#include"Renderer.h"
#include"Core/Logger/Logger.h"
#include"Renderer/RenderCommand.h"
#include"Resource/VertexArray.h"
#include <glm/gtc/matrix_transform.hpp>
namespace SerenEngine {
	DEFINE_RTTI_NO_PARENT(Renderer)
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};
	struct CircleVertex
	{
		glm::vec3 WorldPosition;
		glm::vec3 LocalPosition;
		glm::vec4 Color;
		float Thickness;
		float Fade;
	};

	struct LineVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};
	struct SceneData
	{
		static const uint32_t MaxQuads = 1000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxCircles = 1000;
		static const uint32_t MaxCircleIndices = MaxCircles * 6;
		static const uint32_t MaxLineVertices = 2000;
		//Quad
		VertexArray* QuadVertexArray;
		VertexBuffer* QuadVertexBuffer;
		Shader* QuadShader;
		Texture* WhiteTexture;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
		uint32_t QuadIndexCount = 0;
		//Circle
		VertexArray* CircleVertexArray;
		VertexBuffer* CircleVertexBuffer;
		Shader* CircleShader;
		
		CircleVertex* CircleVertexBufferBase = nullptr;
		CircleVertex* CircleVertexBufferPtr = nullptr;
		uint32_t CircleIndexCount = 0;
		//Line
		VertexArray* LineVertexArray;
		VertexBuffer* LineVertexBuffer;
		Shader* LineShader;

		LineVertex* LineVertexBufferBase = nullptr;
		LineVertex* LineVertexBufferPtr = nullptr;
		uint32_t LineVertexCount = 0;

		glm::vec4 QuadVertexPositions[4];

	};

	static Unique<SceneData> s_SceneData=nullptr;

	void Renderer::EnableBlending(ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) {
		RenderCommand::EnableBlending(source, destination, blendEquation);
	}

	void Renderer::DisableBlending() {
		RenderCommand::DisableBlending();
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}
	void Renderer::OnInit(const ApplicationConfiguration& config ) {
		CORE_LOG_TRACE("Renderer init success");
		RenderCommand::OnInit(config.RendererSpec);
		s_SceneData = CreateUnique<SceneData>();


		// ----------------------
		// Quad Initialization
		// ----------------------

		s_SceneData->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		

		s_SceneData->QuadVertexBuffer = VertexBuffer::Create(nullptr, SceneData::MaxVertices * sizeof(QuadVertex));

		s_SceneData->QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});

		s_SceneData->QuadVertexArray->AddVertexBuffer(s_SceneData->QuadVertexBuffer);

		s_SceneData->QuadVertexBufferBase = new QuadVertex[SceneData::MaxVertices];

		uint32_t* quadIndices = new uint32_t[SceneData::MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < SceneData::MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		IndexBuffer* quadIB = IndexBuffer::Create(quadIndices, SceneData::MaxIndices);
		s_SceneData->QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_SceneData->WhiteTexture = Texture::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_SceneData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_SceneData->QuadShader = Shader::Create("Assets/Shader/Renderer_Quad.glsl");

		// ----------------------
		// Circle Initialization
		// ----------------------

		s_SceneData->CircleVertexArray = VertexArray::Create();
		s_SceneData->CircleVertexBuffer = VertexBuffer::Create(nullptr, SceneData::MaxCircles * 4 * sizeof(CircleVertex));
		s_SceneData->CircleVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_WorldPosition" },
			{ ShaderDataType::Float3, "a_LocalPosition" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float,  "a_Thickness" },
			{ ShaderDataType::Float,  "a_Fade" }
			});
		s_SceneData->CircleVertexArray->AddVertexBuffer(s_SceneData->CircleVertexBuffer);
		s_SceneData->CircleVertexArray->SetIndexBuffer(quadIB); 
		s_SceneData->CircleVertexBufferBase = new CircleVertex[SceneData::MaxCircles * 4];
		s_SceneData->CircleShader = Shader::Create("Assets/Shader/Renderer_Circle.glsl");

		// ----------------------
		// Line Initialization
		// ----------------------

		s_SceneData->LineVertexArray = VertexArray::Create();
		s_SceneData->LineVertexBuffer = VertexBuffer::Create(nullptr, SceneData::MaxLineVertices * sizeof(LineVertex));
		s_SceneData->LineVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
			});
		s_SceneData->LineVertexArray->AddVertexBuffer(s_SceneData->LineVertexBuffer);
		s_SceneData->LineVertexBufferBase = new LineVertex[SceneData::MaxLineVertices];

		s_SceneData->LineShader = Shader::Create("Assets/Shader/Renderer_Line.glsl");

		s_SceneData->QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_SceneData->QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_SceneData->QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_SceneData->QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}
	void Renderer::BeginScene(OrthographicCamera& camera) {
		Clear();
		s_SceneData->QuadShader->Bind();
		s_SceneData->QuadShader->SetMatrix4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_SceneData->QuadShader->SetMatrix4("u_Transform", glm::mat4(1.0f));

		// Circle Shader
		s_SceneData->CircleShader->Bind();
		s_SceneData->CircleShader->SetMatrix4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_SceneData->CircleShader->SetMatrix4("u_Transform", glm::mat4(1.0f));

		// Line Shader
		s_SceneData->LineShader->Bind();
		s_SceneData->LineShader->SetMatrix4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_SceneData->LineShader->SetMatrix4("u_Transform", glm::mat4(1.0f));

		StartBatch();
	}
	void Renderer::OnRender() {
		
	}
	void Renderer::EndScene() {
		Flush();
	}
	void Renderer::Flush()
	{
		// Flush Quad
		if (s_SceneData->QuadIndexCount > 0)
		{
			uint32_t quadDataSize = (uint32_t)((uint8_t*)s_SceneData->QuadVertexBufferPtr - (uint8_t*)s_SceneData->QuadVertexBufferBase);
			s_SceneData->QuadVertexBuffer->SetData(s_SceneData->QuadVertexBufferBase, quadDataSize);

			s_SceneData->WhiteTexture->Bind();
			s_SceneData->QuadShader->Bind();
			RenderCommand::DrawIndexed(s_SceneData->QuadVertexArray, s_SceneData->QuadIndexCount);
		}

		// Flush Circle
		if (s_SceneData->CircleIndexCount > 0)
		{
			uint32_t circleDataSize = (uint32_t)((uint8_t*)s_SceneData->CircleVertexBufferPtr - (uint8_t*)s_SceneData->CircleVertexBufferBase);
			s_SceneData->CircleVertexBuffer->SetData(s_SceneData->CircleVertexBufferBase, circleDataSize);

			s_SceneData->CircleShader->Bind();
			RenderCommand::DrawIndexed(s_SceneData->CircleVertexArray, s_SceneData->CircleIndexCount);
		}

		// Flush Line
		if (s_SceneData->LineVertexCount > 0)
		{
			uint32_t lineDataSize = (uint32_t)((uint8_t*)s_SceneData->LineVertexBufferPtr - (uint8_t*)s_SceneData->LineVertexBufferBase);
			s_SceneData->LineVertexBuffer->SetData(s_SceneData->LineVertexBufferBase, lineDataSize);

			s_SceneData->LineShader->Bind();
			RenderCommand::DrawLines(s_SceneData->LineVertexArray,s_SceneData->LineVertexCount);
		}
	}
	void Renderer::StartBatch()
	{
		// Quad
		s_SceneData->QuadIndexCount = 0;
		s_SceneData->QuadVertexBufferPtr = s_SceneData->QuadVertexBufferBase;

		// Circle
		s_SceneData->CircleIndexCount = 0;
		s_SceneData->CircleVertexBufferPtr = s_SceneData->CircleVertexBufferBase;

		// Line
		s_SceneData->LineVertexCount = 0;
		s_SceneData->LineVertexBufferPtr = s_SceneData->LineVertexBufferBase;
	}
	void Renderer::NextBatch()
	{
		Flush();
		StartBatch();
	}
	void Renderer::OnShutDown() {
		CORE_LOG_TRACE("Renderer is shutdown");
		RenderCommand::OnShutdown();
	}
	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (s_SceneData->QuadIndexCount >= SceneData::MaxIndices)
			NextBatch();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		const glm::vec2 texCoords[4] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};

		glm::vec4 quadVertexPositions[4] = {
			transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
			transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
			transform * glm::vec4(0.5f,  0.5f, 0.0f, 1.0f),
			transform * glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f)
		};

		for (int i = 0; i < 4; i++) {
			s_SceneData->QuadVertexBufferPtr->Position = glm::vec3(quadVertexPositions[i]);
			s_SceneData->QuadVertexBufferPtr->Color = color;
			s_SceneData->QuadVertexBufferPtr->TexCoord = texCoords[i];
			s_SceneData->QuadVertexBufferPtr++;
		}

		s_SceneData->QuadIndexCount += 6;
	}
	void Renderer::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}
	void Renderer::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
	
		if (s_SceneData->QuadIndexCount >= SceneData::MaxIndices)
			NextBatch();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

		const glm::vec2 texCoords[4] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};

		glm::vec4 quadVertexPositions[4] = {
			transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
			transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
			transform * glm::vec4(0.5f,  0.5f, 0.0f, 1.0f),
			transform * glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f)
		};

		for (int i = 0; i < 4; i++) {
			s_SceneData->QuadVertexBufferPtr->Position = glm::vec3(quadVertexPositions[i]);
			s_SceneData->QuadVertexBufferPtr->Color = color;
			s_SceneData->QuadVertexBufferPtr->TexCoord = texCoords[i];
			s_SceneData->QuadVertexBufferPtr++;
		}

		s_SceneData->QuadIndexCount += 6;
	}
	void Renderer::DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness, float fade)
	{
		for (size_t i = 0; i < 4; i++)
		{
			s_SceneData->CircleVertexBufferPtr->WorldPosition = transform * s_SceneData->QuadVertexPositions[i];
			s_SceneData->CircleVertexBufferPtr->LocalPosition = s_SceneData->QuadVertexPositions[i] * 2.0f;
			s_SceneData->CircleVertexBufferPtr->Color = color;
			s_SceneData->CircleVertexBufferPtr->Thickness = thickness;
			s_SceneData->CircleVertexBufferPtr->Fade = fade;
			s_SceneData->CircleVertexBufferPtr++;
		}

		s_SceneData->CircleIndexCount += 6;
	}
	void Renderer::DrawCircle(const glm::vec2& position, float radius, const glm::vec4& color)
	{
		DrawCircle(glm::vec3(position, 0.0f), radius, color);
	}
	void Renderer::DrawCircle(const glm::vec3& position, float radius, const glm::vec4& color)
	{
		if (s_SceneData->CircleIndexCount >= SceneData::MaxCircleIndices)
			NextBatch();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(radius * 2.0f, radius * 2.0f, 1.0f));

		glm::vec3 localPositions[4] = {
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f,  0.5f, 0.0f),
		glm::vec3(-0.5f,  0.5f, 0.0f)
		};

		for (int i = 0; i < 4; i++) {
			CircleVertex& vertex = *s_SceneData->CircleVertexBufferPtr;
			glm::vec4 worldPos = transform * glm::vec4(localPositions[i], 1.0f);
			vertex.WorldPosition = glm::vec3(worldPos);
			vertex.LocalPosition = localPositions[i];
			vertex.Color = color;
			vertex.Thickness = 1.0f; 
			vertex.Fade = 0.005f;    

			s_SceneData->CircleVertexBufferPtr++;
		}

		s_SceneData->CircleIndexCount += 6;
	}
	void Renderer::DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color, float thickness=1.0f)
	{
		DrawLine(glm::vec3(start, 0.0f), glm::vec3(end, 0.0f), color, thickness);
	}
	void Renderer::DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color, float thickness=1.0f)
	{
		if (s_SceneData->LineVertexCount >= SceneData::MaxLineVertices)
			NextBatch();

		s_SceneData->LineVertexBufferPtr->Position = start;
		s_SceneData->LineVertexBufferPtr->Color = color;
		s_SceneData->LineVertexBufferPtr++;

		s_SceneData->LineVertexBufferPtr->Position = end;
		s_SceneData->LineVertexBufferPtr->Color = color;
		s_SceneData->LineVertexBufferPtr++;

		s_SceneData->LineVertexCount += 2;
	}
}