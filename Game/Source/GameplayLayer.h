#pragma once
#include "SerenEngine.h"
#include "Level.h"
#include"imgui.h"
#include"box2d/box2d.h"
class GameplayLayer : public SerenEngine::Layer
{
public:
	GameplayLayer();
	~GameplayLayer() {};
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(SerenEngine::Time time) override;
	virtual void OnImGuiRender() override;
	virtual bool OnKeyPressedEvent(const SerenEngine::KeyPressedEvent& eventContext);
	virtual void OnProcessInput(const SerenEngine::InputState&) override;
	virtual bool OnWindowResizedEvent(const SerenEngine::WindowResizedEvent&) override;
	virtual bool OnMouseButtonPressedEvent(const SerenEngine::MouseButtonPressedEvent&) override;
	//virtual bool OnMouseScrolledEvent(const SerenEngine::MouseScrolledEvent&) override;
private:
	void CreateCameraController(uint32_t width, uint32_t height);
private:
	SerenEngine::Renderer* mRenderer;
	Level m_Level;
	SerenEngine::OrthographicCameraController m_CameraController;
	float m_Time = 0.0f;
	ImFont* m_Font;
	bool m_Blink = false;
	b2World* m_World;
	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};