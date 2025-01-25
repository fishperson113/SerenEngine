#include"Application.h"
#include<iostream>
#include"Core/Logger/Logger.h"

namespace SerenEngine
{
	Application::Application(const ApplictionConfig& config): m_Config(config){
		Logger::Init();
	}

	void Application::Run()
	{
		CORE_LOG_INFO("Application is running {0} {1} {2}", m_Config.WindowHeight, m_Config.WindowWidth, m_Config.WindowTitle);
	}
}