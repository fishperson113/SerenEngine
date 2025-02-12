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

		VertexArray* QuadVertexArray;
		VertexBuffer* QuadVertexBuffer;
		Shader* TextureShader;
		Texture* WhiteTexture;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
		uint32_t QuadIndexCount = 0;
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
		s_SceneData->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		
		VertexBuffer* squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		s_SceneData->QuadVertexBuffer = squareVB;
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_SceneData->QuadVertexArray->AddVertexBuffer(squareVB);
		s_SceneData->QuadVertexBufferBase = new QuadVertex[SceneData::MaxVertices];

		// Tạo index buffer (với các chỉ số cho từng quad)
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

		/*uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		IndexBuffer* squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_SceneData->QuadVertexArray->SetIndexBuffer(squareIB);*/
		IndexBuffer* quadIB = IndexBuffer::Create(quadIndices, SceneData::MaxIndices);
		s_SceneData->QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_SceneData->WhiteTexture = Texture::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_SceneData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_SceneData->TextureShader = Shader::Create("Assets/Shader/Texture.glsl");
		s_SceneData->TextureShader->Bind();
		s_SceneData->TextureShader->SetInt("u_Texture", 0);
	}
	void Renderer::BeginScene(OrthographicCamera& camera) {
		Clear();
		s_SceneData->TextureShader->Bind();
		s_SceneData->TextureShader->SetMatrix4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_SceneData->TextureShader->SetMatrix4("u_Transform", glm::mat4(1.0f));
		StartBatch();
	}
	void Renderer::OnRender() {
		
	}
	void Renderer::EndScene() {
		Flush();
	}
	void Renderer::Flush()
	{
		if (s_SceneData->QuadIndexCount == 0)
			return;

		uint32_t dataSize = (uint32_t)((uint8_t*)s_SceneData->QuadVertexBufferPtr - (uint8_t*)s_SceneData->QuadVertexBufferBase);
		s_SceneData->QuadVertexBuffer->SetData(s_SceneData->QuadVertexBufferBase, dataSize);

		s_SceneData->WhiteTexture->Bind(); 
		s_SceneData->TextureShader->Bind();
		RenderCommand::DrawIndexed(s_SceneData->QuadVertexArray, s_SceneData->QuadIndexCount);
	}
	void Renderer::StartBatch()
	{
		s_SceneData->QuadIndexCount = 0;
		s_SceneData->QuadVertexBufferPtr = s_SceneData->QuadVertexBufferBase;
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
		/*s_SceneData->TextureShader->SetFloats4("u_Color", color);
		s_SceneData->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_SceneData->TextureShader->SetMatrix4("u_Transform", transform);
		s_SceneData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_SceneData->QuadVertexArray, s_SceneData->QuadVertexArray->GetIndexBuffer()->GetNums());*/
		if (s_SceneData->QuadIndexCount >= SceneData::MaxIndices)
			NextBatch();

		s_SceneData->TextureShader->SetFloats4("u_Color", color);
		s_SceneData->WhiteTexture->Bind();
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
	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}
	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		s_SceneData->TextureShader->SetFloats4("u_Color", color);
		s_SceneData->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_SceneData->TextureShader->SetMatrix4("u_Transform", transform);
		s_SceneData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_SceneData->QuadVertexArray, s_SceneData->QuadVertexArray->GetIndexBuffer()->GetNums());
	}
}