#pragma once

#include "Core/Input/InputState.h"
class GLFWwindow;
namespace SerenEngine
{
	enum class EWindowPlatformSpec
	{
		GLFW,
		SDL,
		WinAPI,
		NONE
	};
	class EventDispatcher; 
	struct ApplicationConfiguration;

	struct WindowData
	{
		int32_t Width, Height;
		EventDispatcher* Dispatcher;
		InputState Input;
	};
	class INativeWindow
	{
	public:
		virtual ~INativeWindow() = default;
		virtual bool Init(const struct ApplicationConfiguration&, EventDispatcher*) = 0;
		virtual void Shutdown() = 0;
		virtual void SwapBuffers() = 0;
		virtual void PollEvents() = 0;
		virtual bool ShouldClose() = 0;
		virtual InputState* GetInputState() = 0;
		virtual float GetTimeSeconds() = 0;
		virtual void OnUpdate() = 0;
		virtual int32_t GetWidth() = 0;
		virtual int32_t GetHeight() = 0;
	protected:
		INativeWindow() = default;
		INativeWindow(INativeWindow&) = default;
	};
	class GLFWPlatformWindow : public INativeWindow
	{
	public:
		GLFWPlatformWindow();
		~GLFWPlatformWindow();
		virtual bool Init(const struct ApplicationConfiguration&, EventDispatcher*) override;
		virtual void Shutdown() override;
		virtual void SwapBuffers() override;
		virtual void PollEvents() override;
		virtual bool ShouldClose() override;
		virtual int32_t GetWidth() override;
		virtual int32_t GetHeight() override;
		virtual InputState* GetInputState() override;
		virtual float GetTimeSeconds() override;
		GLFWwindow* GetWindow() const { return m_Window; }
		virtual void OnUpdate() override;
	private:
		GLFWwindow* m_Window;
		WindowData m_WindowData;

	};
}