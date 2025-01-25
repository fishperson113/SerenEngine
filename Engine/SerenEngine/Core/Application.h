#pragma once
#include"pch.h"
#include "Window/Window.h"
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
		ApplicationConfiguration m_Config;
		Unique<INativeWindow> m_NativeWindow;
	};
	extern Application* CreateApplication();
}