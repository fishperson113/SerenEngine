#include"Renderer.h"
#include"Core/Logger/Logger.h"
#include"Renderer/RenderCommand.h"
#include"Resource/VertexArray.h"
#include <glm/gtc/matrix_transform.hpp>
namespace SerenEngine {
	DEFINE_RTTI_NO_PARENT(Renderer)

	Unique<Renderer::SceneData> Renderer::s_SceneData = nullptr;

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
		s_SceneData = CreateUnique<Renderer::SceneData>();
		s_SceneData->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		
		VertexBuffer* squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_SceneData->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		IndexBuffer* squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_SceneData->QuadVertexArray->SetIndexBuffer(squareIB);

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
	}
	void Renderer::OnRender() {
		
	}
	void Renderer::EndScene() {
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
		s_SceneData->TextureShader->SetFloats4("u_Color", color);
		s_SceneData->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_SceneData->TextureShader->SetMatrix4("u_Transform", transform);
		s_SceneData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_SceneData->QuadVertexArray, s_SceneData->QuadVertexArray->GetIndexBuffer()->GetNums());
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