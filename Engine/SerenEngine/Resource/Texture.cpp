#include"Texture.h"
#include"ResourceManager.h"

namespace SerenEngine
{
	DEFINE_RTTI(Texture, Object::RunTimeType)


		Texture* Texture::Create(const char* path)
	{
		return ResourceManager::Get().NewTexture(path);
	}

	Texture* Texture::Create(uint32_t width, uint32_t height)
	{
		return ResourceManager::Get().NewTexture(width,height);
	}

}