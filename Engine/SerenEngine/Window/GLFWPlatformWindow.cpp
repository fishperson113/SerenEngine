#include"Window.h"
#include<Core/Logger/Logger.h>
#include<Core/Application.h>

#define GLAD_GL_IMPLEMENTATION
#include<glad/gl.h>
#include<GLFW/glfw3.h>

namespace SerenEngine {
	GLFWPlatformWindow::GLFWPlatformWindow() : m_Window(nullptr) {}

	GLFWPlatformWindow::~GLFWPlatformWindow() 
	{
	}

	bool GLFWPlatformWindow::Init(const ApplicationConfiguration& config)
	{
		if (!glfwInit())
		{
			CORE_LOG_CRITICAL("Failed to initialize GLFW");
			return false;
		}
		//Setup context OpenGL 4.3 core
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(config.WindowWidth, config.WindowHeight, config.WindowTitle, nullptr, nullptr);

		if (!m_Window)
		{
			CORE_LOG_CRITICAL("Failed to create window");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("Window created succesful");

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
		{
			CORE_LOG_CRITICAL("Failed to initialize GLAD");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("GLAD initialized");
		return true;
	}

	void GLFWPlatformWindow::Shutdown()
	{
		glfwTerminate();
	}
	void GLFWPlatformWindow::SwapBuffers()
	{
		glClearColor(1.1f, 3.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_Window);
	}
	void GLFWPlatformWindow::PollEvents()
	{
		glfwPollEvents();
	}
	bool GLFWPlatformWindow::ShouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}
}