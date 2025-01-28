#pragma once
#include <Core/Layer/Layer.h>
#include<Core/Logger/Logger.h>
class GameplayLayer : public SerenEngine::Layer
{
public:
	GameplayLayer() {}
	~GameplayLayer() {}
	virtual void OnAttach() override {
		LOG_TRACE("GameplayLayer is attached");
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
};