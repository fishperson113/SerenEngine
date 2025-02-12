#pragma once
#include"pch.h"
#include"Core/Type/RTTI.h"
#include"Core/Application.h"
#include"Core/Application.h"
#include"RenderCommandQueue.h"
#include"Resource/VertexBuffer.h"
#include"Resource/IndexBuffer.h"
#include"Resource/VertexArray.h"
#include"Resource/Shader.h"
#include"Resource/Texture.h"
#include"Renderer/OrthographicCamera.h"
namespace SerenEngine {
	class SEREN_API Renderer {
	public:
		DECLARE_RTTI
	public:		
		static void EnableBlending(ERendererBlendFunction source = ERendererBlendFunction::SourceAlpha, ERendererBlendFunction destination = ERendererBlendFunction::OneMinusSourceAlpha, ERendererBlendEquation blendEquation = ERendererBlendEquation::Add);
		static void DisableBlending();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void Clear();
	public:
		 void OnInit(const ApplicationConfiguration&);
		 void OnShutDown();
		 void BeginScene(OrthographicCamera& camera);
		 void OnRender();
		 void EndScene();
	public:
		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		/*static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });*/
	private:
		static void Flush();
		static void StartBatch();
		static void NextBatch();
	};
}