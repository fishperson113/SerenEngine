#pragma once
#include"pch.h"
#include "Window/Window.h"
#include"Window/WindowPlatform.h"
#include <Core/Event/EventDispatcher.h>
#include"Core/Logger/Logger.h"
#include "Layer/LayerStack.h"
#include "Core/Time/Time.h"
namespace SerenEngine
{
	struct SEREN_API ApplicationConfiguration
	{
		int WindowWidth;
		int WindowHeight;
		const char* WindowTitle;
		EWindowPlatformSpec WindowSpec;
		uint16_t MaxFPS;
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

		void PushLayer(Layer*);
		void PushOverlayLayer(Layer*);
		void PopLayer(Layer*);
		void PopOverlayLayer(Layer*);
	private:
		bool OnWindowResizedEvent(const WindowResizedEvent& event);
		bool OnKeyPressedEvent(const KeyPressedEvent&);
		bool OnKeyHeldEvent(const KeyHeldEvent&);
		bool OnKeyReleasedEvent(const KeyReleasedEvent&);
		bool OnMouseMovedEvent(const MouseMovedEvent&);
		bool OnMouseScrolledEvent(const MouseScrolledEvent&);
		bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent&);
		bool OnMouseButtonHeldEvent(const MouseButtonHeldEvent&);
		bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent&);
	private:
		ApplicationConfiguration m_Config;
		Unique<INativeWindow> m_NativeWindow;
		EventDispatcher m_EventDispatcher;
		InputState* m_InputState;
		Unique<LayerStack> mLayerStack;
		Time m_Time;
		bool mIsRunning;
	};
	extern Application* CreateApplication();
}