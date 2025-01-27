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
		FREE_MEMORY(m_WindowData.Input.Keyboard);
		FREE_MEMORY(m_WindowData.Input.Mouse);
	}

	bool GLFWPlatformWindow::Init(const ApplicationConfiguration& config, EventDispatcher* eventDispatcher)
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

		m_WindowData.Dispatcher = eventDispatcher;
		m_WindowData.Input.Keyboard = WindowPlatform::CreateKeyboard(config.WindowSpec, m_Window);
		m_WindowData.Input.Mouse = WindowPlatform::CreateMouse(config.WindowSpec, m_Window);
		glfwSetWindowUserPointer(m_Window, &m_WindowData);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);

			WindowData* data = static_cast<WindowData*> (glfwGetWindowUserPointer(window));
			data->Width = width;
			data->Height = height;
			WindowResizedEvent eventContext(width, height);
			data->Dispatcher->DispatchEvent<WindowResizedEvent>(eventContext);
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keyCode, int scanCode, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			//TODO: Held event
			if (action == GLFW_PRESS) {
				data->Dispatcher->DispatchEvent<KeyPressedEvent>({ keyCode });
			}
			else if (action == GLFW_REPEAT) {
				data->Dispatcher->DispatchEvent<KeyHeldEvent>({ keyCode });
			}
			else if (action == GLFW_RELEASE) {
				data->Dispatcher->DispatchEvent<KeyReleasedEvent>({ keyCode });
			}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			//TODO: Held event
			if (action == GLFW_PRESS) {
				data->Dispatcher->DispatchEvent<MouseButtonPressedEvent>({ button });
			}
			else if (action == GLFW_RELEASE) {
				data->Dispatcher->DispatchEvent<MouseButtonReleasedEvent>({ button });
			}
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double positionX, double positionY) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			static double lastFrameX = positionX;
			static double lastFrameY = positionY;

			double offsetX = positionX - lastFrameX;
			double offsetY = positionY - lastFrameY;

			data->Dispatcher->DispatchEvent<MouseMovedEvent>({ positionX, positionY, offsetX, offsetY });
			data->Input.Mouse->SetPosition(positionX, positionY);
			data->Input.Mouse->SetOffset(offsetX, offsetY);

			lastFrameX = positionX;
			lastFrameY = positionY;
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double scrollX, double scrollY) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->Dispatcher->DispatchEvent<MouseScrolledEvent>({ scrollX, scrollY });
			data->Input.Mouse->SetScroll(scrollX, scrollY);
			});

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
	InputState* GLFWPlatformWindow::GetInputState()
	{
		return &m_WindowData.Input;
	}
}