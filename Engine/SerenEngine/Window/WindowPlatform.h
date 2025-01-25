#pragma once

#include"Window.h"

namespace SerenEngine
{
	class WindowPlatform
	{
	public:
		static INativeWindow* Create(EWinPlatformSpec spec);
	private:
		WindowPlatform() = default;
		WindowPlatform(WindowPlatform&) = default;
		~WindowPlatform() = default;
	};
}