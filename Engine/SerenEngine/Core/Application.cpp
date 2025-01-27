#include"Application.h"
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

	bool Application::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is pressed", (char)eventContext.GetKeyCode());
		return false;
	}

	bool Application::OnKeyHeldEvent(const KeyHeldEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is held", (char)eventContext.GetKeyCode());
		return false;
	}

	bool Application::OnKeyReleasedEvent(const KeyReleasedEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is released", (char)eventContext.GetKeyCode());
		return false;
	}

	bool Application::OnMouseMovedEvent(const MouseMovedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse position: {0}, {1}. Mouse relative: {2}, {3}", eventContext.GetPositionX(), eventContext.GetPositionY(), eventContext.GetOffsetX(), eventContext.GetOffsetY());
		return false;
	}

	bool Application::OnMouseScrolledEvent(const MouseScrolledEvent& eventContext) {
		CORE_LOG_TRACE("Mouse scroll X: {0}, Mouse Scroll Y: {1}", eventContext.GetScrollX(), eventContext.GetScrollY());
		return false;
	}

	bool Application::OnMouseButtonPressedEvent(const MouseButtonPressedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {0} is pressed", eventContext.GetButton());
		return false;
	}

	bool Application::OnMouseButtonHeldEvent(const MouseButtonHeldEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {0} is held", eventContext.GetButton());
		return false;
	}

	bool Application::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {0} is released", eventContext.GetButton());
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
		m_InputState = m_NativeWindow->GetInputState();
		m_EventDispatcher.AddEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(Application::OnWindowResizedEvent));
		m_EventDispatcher.AddEventListener<KeyPressedEvent>(BIND_EVENT_FUNCTION(OnKeyPressedEvent));
		m_EventDispatcher.AddEventListener<KeyHeldEvent>(BIND_EVENT_FUNCTION(OnKeyHeldEvent));
		m_EventDispatcher.AddEventListener<KeyReleasedEvent>(BIND_EVENT_FUNCTION(OnKeyReleasedEvent));
		m_EventDispatcher.AddEventListener<MouseMovedEvent>(BIND_EVENT_FUNCTION(OnMouseMovedEvent));
		m_EventDispatcher.AddEventListener<MouseScrolledEvent>(BIND_EVENT_FUNCTION(OnMouseScrolledEvent));
		m_EventDispatcher.AddEventListener<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(OnMouseButtonPressedEvent));
		m_EventDispatcher.AddEventListener<MouseButtonHeldEvent>(BIND_EVENT_FUNCTION(OnMouseButtonHeldEvent));
		m_EventDispatcher.AddEventListener<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(OnMouseButtonReleasedEvent));
		return true;
	}

	void Application::Run()
	{
		CORE_LOG_INFO("Application is running {0} {1} {2}", m_Config.WindowHeight, m_Config.WindowWidth, m_Config.WindowTitle);
		OnInitClient();

		while (!m_NativeWindow->ShouldClose())
		{
			m_NativeWindow->SwapBuffers();
			
			m_NativeWindow->PollEvents();
		}

		OnShutdownClient();
	}
	void Application::Shutdown()
	{
		m_NativeWindow->Shutdown();
	}
}