#pragma once
#include"pch.h"
class GLFWwindow;
namespace SerenEngine
{
	enum class EWinPlatformSpec
	{
		GLFW,
		SDL,
		NONE
	};
	class EventDispatcher; 

	struct WindowData
	{
		int32_t Width, Height;
		EventDispatcher* Dispatcher;
	};

	class INativeWindow
	{
	public:
		virtual ~INativeWindow() = default;
		virtual bool Init(const struct ApplicationConfiguration&,EventDispatcher*) = 0;
		virtual void Shutdown() = 0;
		virtual void SwapBuffers() = 0;
		virtual void PollEvents() = 0;
		virtual bool ShouldClose() = 0;
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
		GLFWwindow* GetWindow() const { return m_Window; }
	private:
		GLFWwindow* m_Window;
		WindowData m_WindowData;
	};
}