#include"Renderer.h"
#include"Core/Logger/Logger.h"
#include"Renderer/RenderCommand.h"
namespace SerenEngine {
	DEFINE_RTTI_NO_PARENT(Renderer)

	RenderCommandQueue Renderer::sRenderCommandQueue;
	void Renderer::Submit(const RenderCallback& renderCallback) {
		if (Application::Get().GetPerFrameData().IsCatchUpPhase) return;
		sRenderCommandQueue.Enqueue(renderCallback);
	}
	void Renderer::SetClearColor(float r, float g, float b, float w) {
		Submit([r, g, b, w]() {
			RenderCommand::SetClearColor(r, g, b, w);
			});
	}
	void Renderer::EnableBlending(ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) {
		Submit([source, destination, blendEquation]() {
			RenderCommand::EnableBlending(source, destination, blendEquation);
			});
	}

	void Renderer::DisableBlending() {
		Submit([]() {
			RenderCommand::DisableBlending();
			});
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		Submit([width, height]() {
			RenderCommand::SetViewport(0,0,width, height);
			});
	}
	void Renderer::Clear()
	{
		Submit([]() {
			RenderCommand::Clear();
			});
	}
	void Renderer::DrawIndexed(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) {
		Submit([nums, primitive, offset]() {
			RenderCommand::DrawIndexed(nums, primitive, offset);
			});
	}
	Renderer::Renderer() {
	}
	Renderer::~Renderer() {
	}
	void Renderer::OnInit(const ApplicationConfiguration& config ) {
		CORE_LOG_TRACE("Renderer init success");
		Submit([rendererSpec = config.RendererSpec]() {
			RenderCommand::OnInit(rendererSpec);
			});
	}
	bool Renderer::BeginScene() {
		Clear();
		return true;
	}
	void Renderer::Render() {
		sRenderCommandQueue.ProcessAndRender();
	}
	void Renderer::EndScene() {
	}
	void Renderer::OnShutDown() {
		CORE_LOG_TRACE("Renderer is shutdown");
		RenderCommand::OnShutdown();
		Submit([]() {
			RenderCommand::OnShutdown();
			});
	}
}