#pragma once
#include <Core/Layer/Layer.h>
#include<Core/Logger/Logger.h>
#include<Core/Memory/MemoryChunkManager.h>
static size_t Count = 0;

struct Texture {
	Texture() {
		ID = Count++;
	}

	uint32_t ID;
	std::string FilePath;
};
using namespace SerenEngine;
class ResourceManager {

	class TextureManager : public MemoryChunkManager<Texture, 4> {
	public:
		TextureManager(const char* usage, const MemoryConfiguration& config) : MemoryChunkManager(usage, config) {

		}

		Texture* LoadTexture() {
			return NewObject();
		}

		void UnLoad(void* memory) {
			FreeObject(memory);
		}
	};

public:
	ResourceManager() : mTextureManager("TextureManager", {}) {

	}

	Texture* LoadTexture() {
		return mTextureManager.LoadTexture();
	}

	void UnloadTexture(void* memory) {
		mTextureManager.UnLoad(memory);
	}

	void UnloadAllTextures() {
		mTextureManager.Reset();
	}

	void Shutdown() {
		mTextureManager.DetecMemoryLeaks();
	}

private:
	TextureManager mTextureManager;
};
class GameplayLayer : public SerenEngine::Layer
{
public:
	GameplayLayer() {}
	~GameplayLayer() {}
	virtual void OnAttach() override {
		LOG_TRACE("GameplayLayer is attached");

		std::vector<Texture*> textures;

		int count = 10;
		for (int i = 0; i < count; i++) {
			textures.emplace_back(mResourceManager.LoadTexture());
		}

		mResourceManager.UnloadTexture(textures[1]);
		mResourceManager.UnloadTexture(textures[9]);

		mResourceManager.LoadTexture();
		mResourceManager.LoadTexture();

		mResourceManager.UnloadAllTextures();
		textures.clear();

		for (int i = 0; i < count; i++) {
			textures.emplace_back(mResourceManager.LoadTexture());
		}

		mResourceManager.UnloadAllTextures();
		mResourceManager.Shutdown();

		CORE_LOG_WARN("Testing point");
	}
	virtual void OnDetach() override {
		LOG_TRACE("GameplayLayer is detached");
	}
	virtual bool OnKeyPressedEvent(const SerenEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed", (char)eventContext.GetKeyCode());
		return false;
	}
	virtual void OnUpdate(SerenEngine::Time deltaTime) override {
		//LOG_TRACE("GameplayLayer is updated at {0} ", deltaTime.GetDeltaTime());
	}
private:
	ResourceManager mResourceManager;
};