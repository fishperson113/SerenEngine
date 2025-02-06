#include"ResourceManager.h"
#include"Core/GlobalMemory.h"
#include"Renderer/OpenGL/OpenGLResourceManager.h"

namespace SerenEngine {
	ResourceManager* ResourceManager::sInstance = nullptr;

	ResourceManager& ResourceManager::Get()
	{
		return *sInstance;
	}

	void ResourceManager::OnInit(ERendererSpec rendererSpec)
	{
		switch (rendererSpec)
		{
		case SerenEngine::ERendererSpec::OpenGL:
			sInstance = GlobalMemoryUsage::Get().NewOnStack<OpenGLResourceManager>(OpenGLResourceManager::RunTimeType.GetTypeName());
			break;
		case SerenEngine::ERendererSpec::DirectX:
			ASSERT("Currently not supported for Direct X");
			break;
		default:
			ASSERT("Unkown renderer spec!");
			break;
		}
	}

	void ResourceManager::OnShutdown()
	{
		sInstance->OnReset();
	}
}