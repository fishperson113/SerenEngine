#pragma once

#include "pch.h"

namespace SerenEngine
{
	class SEREN_API EventContext
	{
	public:
		virtual ~EventContext() = default;
	};
	class SEREN_API WindowResizedEvent : public EventContext
	{
	private:
		int32_t m_Width;
		int32_t m_Height;
	public:
		WindowResizedEvent(int32_t width, int32_t height) : m_Width(width), m_Height(height) {}
		FORCE_INLINE int32_t GetWidth() const { return m_Width; }
		FORCE_INLINE int32_t GetHeight() const { return m_Height; }
	};
	class SEREN_API KeyPressedEvent : public EventContext {
	public:
		KeyPressedEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		FORCE_INLINE int32_t GetKeyCode() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	};

	class SEREN_API KeyHeldEvent : public EventContext {
	public:
		KeyHeldEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		FORCE_INLINE int32_t GetKeyCode() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	};

	class SEREN_API KeyReleasedEvent : public EventContext {
	public:
		KeyReleasedEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		FORCE_INLINE int32_t GetKeyCode() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	};

	class SEREN_API MouseMovedEvent : public EventContext {
	public:
		MouseMovedEvent(double x, double y, double offsetX, double offsetY) :
			xPosition(x), yPosition(y),
			xOffset(offsetX), yOffset(offsetY) {}
		FORCE_INLINE double GetX() const { return xPosition; }
		FORCE_INLINE double GetY() const { return yPosition; }
		FORCE_INLINE double GetOffsetX() const { return xOffset; }
		FORCE_INLINE double GetOffsetY() const { return yOffset; }
	private:
		double xPosition, yPosition;
		double xOffset, yOffset;
	};

	class SEREN_API MouseScrolledEvent : public EventContext {
	public:
		MouseScrolledEvent(double offsetX, double offsetY) : xOffset(offsetX), yOffset(offsetY) {}
		FORCE_INLINE double GetOffsetX() const { return xOffset; }
		FORCE_INLINE double GetOffsetY() const { return yOffset; }
	private:
		double xOffset, yOffset;
	};

	class SEREN_API MouseButtonPressedEvent : public EventContext {
	public:
		MouseButtonPressedEvent(int32_t button) : mButton(button) {}
		FORCE_INLINE int32_t GetButton() const { return mButton; }
	private:
		int32_t mButton;
	};

	class SEREN_API MouseButtonHeldEvent : public EventContext {
	public:
		MouseButtonHeldEvent(int32_t button) : mButton(button) {}
		FORCE_INLINE int32_t GetButton() const { return mButton; }
	private:
		int32_t mButton;
	};

	class SEREN_API MouseButtonReleasedEvent : public EventContext {
	public:
		MouseButtonReleasedEvent(int32_t button) : mButton(button) {}
		FORCE_INLINE int32_t GetButton() const { return mButton; }
	private:
		int32_t mButton;
	};
}