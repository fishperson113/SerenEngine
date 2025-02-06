#include"RenderCommand.h"
#include"Core/GlobalMemory.h"
namespace SerenEngine {
	RenderCommand* RenderCommand::sInstance = nullptr;
	void RenderCommand::OnInit(ERendererSpec rendererSpec) {
		switch (rendererSpec)
		{
		case SerenEngine::ERendererSpec::OpenGL:
			sInstance = GlobalMemoryUsage::Get().NewOnStack<OpenGLRenderCommand>(OpenGLRenderCommand::RunTimeType.GetTypeName());
			break;
		case SerenEngine::ERendererSpec::DirectX:
			ASSERT(false && "Currently not supported for DirectX");
			break;
		default:
			ASSERT(false && "Unknow Renderer API");
			break;
		}
	}
	void RenderCommand::OnShutdown() {
		GlobalMemoryUsage::Get().FreeOnStack(sInstance);
	}
}