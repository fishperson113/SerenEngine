#include"Renderer.h"
#include"Core/Logger/Logger.h"
#include"Renderer/RenderCommand.h"
namespace SerenEngine {
	DEFINE_RTTI_NO_PARENT(Renderer)
		Renderer::Renderer() {
	}
	Renderer::~Renderer() {
	}
	void Renderer::OnInit(const ApplicationConfiguration& config ) {
		CORE_LOG_TRACE("Renderer init success");
		RenderCommand::OnInit(config.RendererSpec);
	}
	bool Renderer::BeginScene() {
		return true;
	}
	void Renderer::Render() {
	}
	void Renderer::EndScene() {
	}
	void Renderer::OnShutDown() {
		CORE_LOG_TRACE("Renderer is shutdown");
		RenderCommand::OnShutdown();
	}
}