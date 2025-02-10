#pragma once

#include"pch.h"
#include"Platform/WindowPlatform.h"
#include"Core/Event/EventDispatcher.h"
#include"Core/Layer/LayerStack.h"
#include"Core/Time/Time.h"
#include"Renderer/RendererAPI.h"
#include"ImGUI/ImGuiLayer.h"
#include"Renderer/OrthographicCameraController.h"
namespace SerenEngine {
	struct SEREN_API ApplicationConfiguration {
		int Width, Height;
		const char* Title;
		EWindowPlatformSpec WindowSpec;
		uint16_t MaxFPS;
		ERendererSpec RendererSpec;
	};
	struct SEREN_API PerFrameData {
		uint32_t FrameIndex = 0;
		bool IsCatchUpPhase = false;
	};
	namespace ECS {
		class SystemManager;
		class Coordinator;
	}

	class SEREN_API Application {
	public:
		static Application& Get();
	private:
		static Application* sInstance;
	public:
		virtual ~Application() = default;
		bool Init();
		virtual void OnInitClient() = 0;
		void Run();
		virtual void OnShutdownClient() = 0;
		void Shutdown();
		FORCE_INLINE INativeWindow* GetWindow() const { return mNativeWindow.get(); }
		FORCE_INLINE const PerFrameData& GetPerFrameData() const { return mPerFrameData; }
	protected:
		Application() = default;
		Application(const ApplicationConfiguration&);

		void PushLayer(Layer*);
		void PushOverlayLayer(Layer*);
		void PopLayer(Layer*);
		void PopOverlayLayer(Layer*);
	private:
		bool OnWindowResizedEvent(const WindowResizedEvent&);
		bool OnKeyPressedEvent(const KeyPressedEvent&);
		bool OnKeyHeldEvent(const KeyHeldEvent&);
		bool OnKeyReleasedEvent(const KeyReleasedEvent&);
		bool OnMouseMovedEvent(const MouseMovedEvent&);
		bool OnMouseScrolledEvent(const MouseScrolledEvent&);
		bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent&);
		bool OnMouseButtonHeldEvent(const MouseButtonHeldEvent&);
		bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent&);
	private:
		ApplicationConfiguration mConfig;
		Unique<INativeWindow> mNativeWindow;
		LayerStack* mLayerStack;
		ECS::SystemManager* mSystemManager;
		ECS::Coordinator* mCoordinator;
		class Renderer* mRenderer;
		EventDispatcher mEventDispatcher;
		class InputState* mInputState;
		OrthographicCameraController mCamera;
		Time mTime;
		bool mIsRunning;
		PerFrameData mPerFrameData;
		ImGuiLayer* m_ImGuiLayer;
	};

	extern Application* CreateApplication();
}