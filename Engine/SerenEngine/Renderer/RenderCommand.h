#pragma once
#include"pch.h"
#include"RendererAPI.h"
#include"Core/Type/RTTI.h"
#include"Resource/VertexArray.h"
namespace SerenEngine {
	struct SEREN_API RenderData {
		ERendererState EnableRendererState = ERendererState::None;
		ERendererBlendEquation BlendEquation = ERendererBlendEquation::Add;
		ERendererBlendFunction BlendSource = ERendererBlendFunction::None;
		ERendererBlendFunction BlendDestination = ERendererBlendFunction::None;

		ERendererState DisableRendererState = ERendererState::None;
	};
	class SEREN_API RenderCommand {
	public:
		static void SetClearColor(float r, float g, float b, float w=1.0f) { sInstance->SetClearColorImpl(r, g, b, w); }
		static void DrawIndexed(const Shared<VertexArray>& vertexArray, uint32_t indexCount, ERendererPrimitive primitive, uint32_t offset) { sInstance->DrawIndexedImpl(vertexArray, indexCount, primitive, offset); };
		static void DrawIndexed(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) { sInstance->DrawIndexedImpl(nums, primitive, offset); }
		static void DrawIndexed(VertexArray* vertexArray, uint32_t indexCount, ERendererPrimitive primitive=ERendererPrimitive::Triangles, uint32_t offset=0) { sInstance->DrawIndexedImpl(vertexArray, indexCount, primitive, offset); };
		static void EnableBlending(ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) { sInstance->EnableBlendingImpl(source, destination, blendEquation); }
		static void DisableBlending() { sInstance->DisableBlendingImpl(); }
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { sInstance->SetViewportImpl(x, y, width, height); }
		static void Clear() { sInstance->ClearImpl(); }
		static void DrawLines(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) { sInstance->DrawLinesImpl(nums, primitive, offset); };
		static void SetLineWidth(float width) { sInstance->SetLineWidthImpl(width); };
	protected:
		virtual void SetLineWidthImpl(float width) = 0;
		virtual void DrawLinesImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) = 0;
		virtual void SetClearColorImpl(float r, float g, float b, float w) = 0;
		virtual void DrawIndexedImpl(const Shared<VertexArray>& vertexArray, uint32_t indexCount, ERendererPrimitive primitive, uint32_t offset)=0;
		virtual void DrawIndexedImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) = 0;
		virtual void DrawIndexedImpl(VertexArray* vertexArray, uint32_t indexCount, ERendererPrimitive primitive, uint32_t offset) = 0;
		
		virtual void EnableBlendingImpl(ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) = 0;
		virtual void DisableBlendingImpl() = 0;
		virtual void SetViewportImpl(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void ClearImpl() = 0;
	public:
		static void OnInit(ERendererSpec rendererSpec);
		static void OnShutdown();
	public:
		virtual ~RenderCommand() = default;
	protected:
		RenderCommand() = default;
	protected:
		static RenderCommand* sInstance;
	};
	class OpenGLRenderCommand : public RenderCommand {
	public:
		DECLARE_RTTI
	public:
		OpenGLRenderCommand();
		~OpenGLRenderCommand();
	protected:
		virtual void SetLineWidthImpl(float width) override;
		virtual void DrawLinesImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) override;
		virtual void DrawIndexedImpl(const Shared<VertexArray>& vertexArray, uint32_t indexCount, ERendererPrimitive primitive, uint32_t offset) override;
		virtual void DrawIndexedImpl(VertexArray* vertexArray, uint32_t indexCount, ERendererPrimitive primitive, uint32_t offset) override;
		virtual void SetClearColorImpl(float r, float g, float b, float w = 1.0f) override;
		virtual void DrawIndexedImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) override;
		virtual void EnableBlendingImpl(ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) override;
		virtual void DisableBlendingImpl() override;
		virtual void SetViewportImpl(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void ClearImpl() override;
	private:
		RenderData mRenderData;
	};
}