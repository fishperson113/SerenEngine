#include"Application.h"
#include<iostream>
#include"Core/Logger/Logger.h"
#include "Window/WindowPlatform.h"
namespace SerenEngine
{
	Application::Application(const ApplicationConfiguration& config): m_Config(config),m_EventDispatcher(){
		m_NativeWindow.reset(WindowPlatform::Create(m_Config.WindowSpec));

	}

	bool Application::OnWindowResizedEvent(const WindowResizedEvent& windowResiedEvent)
	{
		CORE_LOG_TRACE("Window Resized Event {0} {1}", windowResiedEvent.GetWidth(), windowResiedEvent.GetHeight());
		return false;
	}

	bool Application::Init()
	{
		Logger::Init();
		if (!m_NativeWindow->Init(m_Config,&m_EventDispatcher))
		{
			CORE_LOG_CRITICAL("Failed to initialize window");
			return false;
		}

		m_EventDispatcher.AddEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(Application::OnWindowResizedEvent));
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