#include <SerenEngine/Core/EntryPoint.h>
#include <iostream>
#include <Core/Logger/Logger.h>
class Game : public SerenEngine::Application
{
	public :
		Game(const SerenEngine::ApplictionConfig& config) : Application(config) {
		}
		~Game() = default;
		virtual bool Init() override
		{
			LOG_INFO("Game init");
			return true;
		}
		virtual void Shutdown() override
		{
			LOG_INFO("Game shutdown");
		}
};
SerenEngine::Application* SerenEngine::CreateApplication()
{
	ApplictionConfig m_Config = { 1280, 720, "Seren Engine" };
	return new Game(m_Config);
}