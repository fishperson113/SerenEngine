#include"Application.h"
#include"Memory/MemoryMonitor.h"
#define DISPATCH_LAYER_EVENT(eventType, eventContext) for (auto iter = mLayerStack->rbegin(); iter != mLayerStack->rend(); ++iter) {\
	if ((*iter)->On##eventType(eventContext)) {\
		break;\
	}\
}
namespace SerenEngine
{
	Application::Application(const ApplicationConfiguration& config): m_Config(config),m_EventDispatcher(),mIsRunning(true){
		m_NativeWindow.reset(WindowPlatform::Create(m_Config.WindowSpec));
		mLayerStack.reset(new LayerStack());
	}

	bool Application::OnWindowResizedEvent(const WindowResizedEvent& eventContext)
	{
		DISPATCH_LAYER_EVENT(WindowResizedEvent, eventContext);
		return false;
	}

	bool Application::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
		if (eventContext.IsKey(EKeyCode::ESCAPE)) {
			mIsRunning = false;
			return true;
		}
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
		const float MAX_DELTA_TIME = 0.05f;
		float minDeltaTime = 1.0f / m_Config.MaxFPS;
		OnInitClient();

		while (mIsRunning && !m_NativeWindow->ShouldClose())
		{
			static float lastFrameTime = 0.0f;

			while (m_NativeWindow->GetTimeSeconds() - lastFrameTime < minDeltaTime);
			MemoryMonitor::Get().Update();

			float currentFrameTime = m_NativeWindow->GetTimeSeconds();

			m_Time = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;

			m_NativeWindow->PollEvents();
			for (auto layer : *mLayerStack.get()) {
				layer->OnProcessInput(*m_InputState);
			}
			m_NativeWindow->SwapBuffers();
			while (m_Time.GetDeltaTime() > MAX_DELTA_TIME) {
				for (auto layer : *mLayerStack.get()) {
					layer->OnUpdate(MAX_DELTA_TIME);
				}
				for (auto layer : *mLayerStack.get()) {
					layer->OnRender();
				}
				m_Time -= MAX_DELTA_TIME;
			}

			for (auto layer : *mLayerStack.get()) {
				layer->OnUpdate(m_Time);
			}

			for (auto layer : *mLayerStack.get()) {
				layer->OnRender();
			}
		}

		OnShutdownClient();
	}
	void Application::Shutdown()
	{
		m_NativeWindow->Shutdown();
		MemoryMonitor::Get().Clear();
		MemoryMonitor::Get().DectecMemoryLeaks();
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