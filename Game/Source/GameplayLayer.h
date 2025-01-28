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
};
class UILayer : public SerenEngine::Layer {
public:
	UILayer() {}
	~UILayer() {}
	virtual void OnAttach() override {
		LOG_TRACE("UILayer is attached");
	}
	virtual void OnDetach() override {
		LOG_TRACE("UILayer is detached");
	}
	virtual bool OnKeyPressedEvent(const SerenEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed on UILayer", (char)eventContext.GetKeyCode());
		return true;
	}

	virtual bool OnKeyReleasedEvent(const SerenEngine::KeyReleasedEvent& eventContext) override {
		if (eventContext.IsKey(SerenEngine::EKeyCode::ESCAPE)) {
			LOG_TRACE("ESC key is released");
		}
		return true;
	}
	virtual bool OnMouseButtonPressedEvent(const SerenEngine::MouseButtonPressedEvent& eventContext) override {
		if (eventContext.IsButton(SerenEngine::EMouseButton::BUTTON_LEFT)) {
			LOG_TRACE("Left mouse button is clicked");
		}
		return true;
	}
};