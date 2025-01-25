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
	class INativeWindow
	{
	public:
		//virtual ~INativeWindow() = default;
		virtual bool Init(const struct ApplicationConfiguration&) = 0;
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
		virtual bool Init(const struct ApplicationConfiguration&) override;
		virtual void Shutdown() override;
		virtual void SwapBuffers() override;
		virtual void PollEvents() override;
		virtual bool ShouldClose() override;
		GLFWwindow* GetWindow() const { return m_Window; }
	private:
		GLFWwindow* m_Window;
	};
}