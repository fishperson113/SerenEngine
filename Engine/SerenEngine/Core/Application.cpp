#include"Application.h"
#include<iostream>
#include"Core/Logger/Logger.h"
#include "Window/WindowPlatform.h"
namespace SerenEngine
{
	Application::Application(const ApplicationConfiguration& config): m_Config(config){
		m_NativeWindow.reset(WindowPlatform::Create(m_Config.WindowSpec));

	}

	bool Application::Init()
	{
		Logger::Init();
		if (!m_NativeWindow->Init(m_Config))
		{
			CORE_LOG_CRITICAL("Failed to initialize window");
			return false;
		}
		return true;
	}

	void Application::Run()
	{
		CORE_LOG_INFO("Application is running {0} {1} {2}", m_Config.WindowHeight, m_Config.WindowWidth, m_Config.WindowTitle);
		OnInitClient();

		while (!m_NativeWindow->ShouldClose())
		{
			m_NativeWindow->PollEvents();
			m_NativeWindow->SwapBuffers();
		}

		OnShutdownClient();
	}
	void Application::Shutdown()
	{
		m_NativeWindow->Shutdown();
	}
}