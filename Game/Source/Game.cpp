#include <SerenEngine/Core/EntryPoint.h>
#include <SerenEngine/Window/Window.h>
#include <Core/Logger/Logger.h>
#include"GameplayLayer.h"
class Game : public SerenEngine::Application
{
public :
	Game(const SerenEngine::ApplicationConfiguration& config) : Application(config) {
	}
	~Game() = default;
	virtual void OnInitClient() override
	{
		LOG_INFO("Game init");
		mLayer = new GameplayLayer();
		mUI = new UILayer();
		PushOverlayLayer(mUI);
		PushLayer(mLayer);

	}
	virtual void OnShutdownClient() override
	{
		LOG_INFO("Game shutdown");
		PopLayer(mLayer);
		PopOverlayLayer(mUI);
	}
private:
	SerenEngine::Layer* mLayer, * mUI;
};
SerenEngine::Application* SerenEngine::CreateApplication()
{
	ApplicationConfiguration m_Config = { 1280, 720, "Seren Engine", EWindowPlatformSpec::GLFW };
	return new Game(m_Config);
}