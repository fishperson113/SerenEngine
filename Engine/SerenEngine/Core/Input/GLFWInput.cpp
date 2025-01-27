#include "InputState.h"
#include <GLFW/glfw3.h>

namespace SerenEngine {
	static EKeyState GLFWKeyStateToEngineKeyState(int32_t state) {
		switch (state)
		{
		case GLFW_PRESS: return EKeyState::Pressed;
		case GLFW_RELEASE: return EKeyState::Released;
		case GLFW_REPEAT: return EKeyState::Held;
		}
		return EKeyState::None;
	}
	GLFWKeyboardInput::GLFWKeyboardInput(void* window) {
		m_Window = (GLFWwindow*)window;
	}

	EKeyState GLFWKeyboardInput::GetState(int32_t keyCode) const {
		return GLFWKeyStateToEngineKeyState(glfwGetKey(m_Window, keyCode));
	}

	bool GLFWKeyboardInput::IsPressed(int32_t keyCode) const {
		return glfwGetKey(m_Window, keyCode) == GLFW_PRESS;
	}

	bool GLFWKeyboardInput::IsHeld(int32_t keyCode) const {
		// TODO: Not use this method, it not work on GLFW
		return glfwGetKey(m_Window, keyCode) == GLFW_REPEAT;
	}

	bool GLFWKeyboardInput::IsReleased(int32_t keyCode) const {
		return glfwGetKey(m_Window, keyCode) == GLFW_RELEASE;
	}
	GLFWMouseInput::GLFWMouseInput(void* window) {
		m_Window = (GLFWwindow*)window;
	}
	EKeyState GLFWMouseInput::GetState(int32_t button) const {
		return GLFWKeyStateToEngineKeyState(glfwGetMouseButton(m_Window, button));
	}

	bool GLFWMouseInput::IsPressed(int32_t button) const {
		return glfwGetMouseButton(m_Window, button) == GLFW_PRESS;
	}

	bool GLFWMouseInput::IsHeld(int32_t button) const {
		// TODO: Not use this method, it not work on GLFW
		return glfwGetMouseButton(m_Window, button) == GLFW_REPEAT;
	}

	bool GLFWMouseInput::IsReleased(int32_t button) const {
		return glfwGetMouseButton(m_Window, button) == GLFW_RELEASE;
	}
}