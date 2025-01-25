#include <SerenEngine/Core/EntryPoint.h>
#include <SerenEngine/Window/Window.h>
#include <iostream>
#include <Core/Logger/Logger.h>
class Game : public SerenEngine::Application
{
	public :
		Game(const SerenEngine::ApplicationConfiguration& config) : Application(config) {
		}
		~Game() = default;
		virtual void OnInitClient() override
		{
			LOG_INFO("Game init");
		}
		virtual void OnShutdownClient() override
		{
			LOG_INFO("Game shutdown");
		}
};
SerenEngine::Application* SerenEngine::CreateApplication()
{
	ApplicationConfiguration m_Config = { 1280, 720, "Seren Engine", EWinPlatformSpec::GLFW };
	return new Game(m_Config);
}