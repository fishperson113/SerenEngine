#pragma once
#include <Core/Layer/Layer.h>
#include<Core/Logger/Logger.h>
#include<Core/Memory/MemoryAllocator.h>
class GameplayLayer : public SerenEngine::Layer
{
public:
	GameplayLayer() {}
	~GameplayLayer() {}
	virtual void OnAttach() override {
		LOG_TRACE("GameplayLayer is attached");

		size_t size = 128 * 1024 * 1024;
		void* address = malloc(size);
		mMemoryAllocator = new SerenEngine::LinearAllocator(size, address);

		struct GameObject {
			size_t ID = 0;
			std::string Name = "GameObject";
		};

		std::vector<GameObject*> gameObjects;
		for (int i = 0; i < 10000; i++) {
			void* memory = mMemoryAllocator->Allocate(sizeof(GameObject), alignof(GameObject));
			GameObject* go = new (memory)GameObject();
			go->ID = i;
			go->Name = "GameObject: " + std::to_string(i);
			gameObjects.emplace_back(go);
		}

		mMemoryAllocator->Clear();
		gameObjects.clear();
		for (int i = 0; i < 10000; i++) {
			void* memory = mMemoryAllocator->Allocate(sizeof(GameObject), alignof(GameObject));
			GameObject* go = new (memory)GameObject();
			go->ID = i + 10000;
			go->Name = "GameObject: " + std::to_string(i);
			gameObjects.emplace_back(go);
		}
		mMemoryAllocator->Clear();
		gameObjects.clear();
	}
	virtual void OnDetach() override {
		LOG_TRACE("GameplayLayer is detached");
	}
	virtual bool OnKeyPressedEvent(const SerenEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed", (char)eventContext.GetKeyCode());
		return false;
	}
	virtual void OnUpdate(SerenEngine::Time deltaTime) override {
		LOG_TRACE("GameplayLayer is updated at {0} ", deltaTime.GetDeltaTime());
	}
private:
	SerenEngine::MemoryAllocator* mMemoryAllocator;
};