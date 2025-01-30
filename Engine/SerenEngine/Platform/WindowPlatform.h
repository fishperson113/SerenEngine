#pragma once

#include"Window.h"

namespace SerenEngine
{
	class WindowPlatform
	{
	public:
		static INativeWindow* Create(EWindowPlatformSpec spec);
		static KeyboardInput* CreateKeyboard(EWindowPlatformSpec spec,void* window);
		static MouseInput* CreateMouse(EWindowPlatformSpec spec, void* window);
	private:
		WindowPlatform() = default;
		WindowPlatform(WindowPlatform&) = default;
		~WindowPlatform() = default;
	};
}