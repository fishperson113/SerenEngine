#include"Application.h"
#define DISPATCH_LAYER_EVENT(eventType, eventContext) for (auto iter = mLayerStack->rbegin(); iter != mLayerStack->rend(); ++iter) {\
	if ((*iter)->On##eventType(eventContext)) {\
		break;\
	}\
}
namespace SerenEngine
{
	Application::Application(const ApplicationConfiguration& config): m_Config(config),m_EventDispatcher(){
		m_NativeWindow.reset(WindowPlatform::Create(m_Config.WindowSpec));
		mLayerStack.reset(new LayerStack());
	}

	bool Application::OnWindowResizedEvent(const WindowResizedEvent& eventContext)
	{
		DISPATCH_LAYER_EVENT(WindowResizedEvent, eventContext);
		return false;
	}

	bool Application::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(KeyPressedEvent, eventContext);
		return false;
	}

	bool Application::OnKeyHeldEvent(const KeyHeldEvent& eventContext) {
		DISPATCH_LAYER_EVENT(KeyHeldEvent, eventContext);
		return false;
	}

	bool Application::OnKeyReleasedEvent(const KeyReleasedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(KeyReleasedEvent, eventContext);
		return false;
	}

	bool Application::OnMouseMovedEvent(const MouseMovedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseMovedEvent, eventContext);
		return false;
	}

	bool Application::OnMouseScrolledEvent(const MouseScrolledEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseScrolledEvent, eventContext);
		return false;
	}

	bool Application::OnMouseButtonPressedEvent(const MouseButtonPressedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonPressedEvent, eventContext);	
		return false;
	}

	bool Application::OnMouseButtonHeldEvent(const MouseButtonHeldEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonHeldEvent, eventContext);
		return false;
	}

	bool Application::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonReleasedEvent, eventContext);
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
			for (auto layer : *mLayerStack.get()) {
				layer->OnProcessInput(*m_InputState);
			}

			for (auto layer : *mLayerStack.get()) {
				layer->OnUpdate(0.0f);
			}
			m_NativeWindow->PollEvents();

			for (auto layer : *mLayerStack.get()) {
				layer->OnRender();
			}
		}

		OnShutdownClient();
	}
	void Application::Shutdown()
	{
		m_NativeWindow->Shutdown();
	}
	void Application::PushLayer(Layer* layer) {
		mLayerStack->Push(layer);
		layer->OnAttach();
	}
	void Application::PushOverlayLayer(Layer* layer) {
		mLayerStack->PushOverlay(layer);
		layer->OnAttach();
	}
	void Application::PopLayer(Layer* layer) {
		mLayerStack->Pop(layer);
		layer->OnDetach();
	}

	void Application::PopOverlayLayer(Layer* layer) {
		mLayerStack->PopOverlay(layer);
		layer->OnDetach();
	}
}