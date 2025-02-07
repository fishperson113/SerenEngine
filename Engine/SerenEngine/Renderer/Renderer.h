#pragma once
#include"pch.h"
#include"Core/Type/RTTI.h"
#include"Core/Application.h"
#include"Core/Application.h"
#include"RenderCommandQueue.h"
namespace SerenEngine {
	struct SEREN_API RendererData {
		ERendererState RendererState = ERendererState::None;
	};
	class SEREN_API Renderer {
	public:
		DECLARE_RTTI
	public:
		static void Submit(const RenderCallback&);
		static void SetClearColor(float r, float g, float b, float w = 1.0f);
		static void DrawIndexed(uint32_t nums, ERendererPrimitive primitive = ERendererPrimitive::Triangles, uint32_t offset = 0);
		static void EnableBlending(ERendererBlendFunction source = ERendererBlendFunction::SourceAlpha, ERendererBlendFunction destination = ERendererBlendFunction::OneMinusSourceAlpha, ERendererBlendEquation blendEquation = ERendererBlendEquation::Add);
		static void DisableBlending();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void Clear();
	private:
		static RenderCommandQueue sRenderCommandQueue;
	public:
		Renderer();
		~Renderer();
		void OnInit(const ApplicationConfiguration&);
		bool BeginScene();
		void Render();
		void EndScene();
		void OnShutDown();
	};
}