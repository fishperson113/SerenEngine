#pragma once
#include"pch.h"
#include "Window/Window.h"
#include <Core/Event/EventDispatcher.h>
namespace SerenEngine
{
	struct SEREN_API ApplicationConfiguration
	{
		int WindowWidth;
		int WindowHeight;
		const char* WindowTitle;
		EWinPlatformSpec WindowSpec;
	};
	class SEREN_API Application
	{
	public:
		virtual ~Application() = default;
		bool Init();
		virtual void OnInitClient()=0;
		void Run();
		void Shutdown();
		virtual void OnShutdownClient() = 0;
	protected:
		Application() = default;
		Application(const ApplicationConfiguration& config);
	private:
		bool OnWindowResizedEvent(const WindowResizedEvent& event);
	private:
		ApplicationConfiguration m_Config;
		Unique<INativeWindow> m_NativeWindow;
		EventDispatcher m_EventDispatcher;
	};
	extern Application* CreateApplication();
}