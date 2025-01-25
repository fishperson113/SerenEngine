#include "WindowPlatform.h"
#include"pch.h"
namespace SerenEngine
{
	INativeWindow* WindowPlatform::Create(EWinPlatformSpec spec)
	{
		INativeWindow* window = nullptr;
		switch (spec)
		{
			case EWinPlatformSpec::GLFW:
				window = new GLFWPlatformWindow();
				break;
			case EWinPlatformSpec::SDL:
				ASSERT(false, "SDL not supported yet");
				break;
			case EWinPlatformSpec::NONE:
				ASSERT(false, "No window platform specified");
				break;
			default:
				ASSERT(false, "No window platform specified");
				break;
		}
		return dynamic_cast<INativeWindow*>(window);
	}
}
