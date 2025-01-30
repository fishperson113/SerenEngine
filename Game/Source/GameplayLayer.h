#pragma once
#include <Core/Layer/Layer.h>
class GameplayLayer : public SerenEngine::Layer
{
public:
	GameplayLayer() {}
	~GameplayLayer() {}
private:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(SerenEngine::Time time);
	virtual bool OnKeyPressedEvent(const SerenEngine::KeyPressedEvent& eventContext);
};