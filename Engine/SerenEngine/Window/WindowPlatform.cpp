#include "WindowPlatform.h"
#include"pch.h"
#include "Core/Input/InputState.h"
namespace SerenEngine
{
	INativeWindow* WindowPlatform::Create(EWindowPlatformSpec spec)
	{
		INativeWindow* window = nullptr;
		switch (spec)
		{
			case EWindowPlatformSpec::GLFW: window = new GLFWPlatformWindow(); break;
			case EWindowPlatformSpec::SDL: ASSERT("SDL Window not supported"); break;
			case EWindowPlatformSpec::NONE: default: ASSERT("Unknown Window detected");
		}
		return window;
	}
	KeyboardInput* WindowPlatform::CreateKeyboard(EWindowPlatformSpec spec, void* window)
	{
		KeyboardInput* input = nullptr;
		switch (spec)
		{
		case EWindowPlatformSpec::GLFW: input = new GLFWKeyboardInput(window); break;
		case EWindowPlatformSpec::SDL: ASSERT("SDL Keyboard not supported"); break;
		case EWindowPlatformSpec::NONE: default: ASSERT("Unknown keyboard detected");
		}
		return input;
	}
	MouseInput* WindowPlatform::CreateMouse(EWindowPlatformSpec spec, void* window)
	{
		MouseInput* input = nullptr;
		switch (spec)
		{
		case EWindowPlatformSpec::GLFW: input = new GLFWMouseInput(window); break;
		case EWindowPlatformSpec::SDL: ASSERT("SDL Mouse not supported"); break;
		case EWindowPlatformSpec::NONE: default: ASSERT("Unknown Mouse detected");
		}
		return input;
	}
}
