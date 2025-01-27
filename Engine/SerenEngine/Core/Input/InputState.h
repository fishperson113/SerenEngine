#pragma once
#include "pch.h"
#include "Keycode.h"

class GLFWwindow;

namespace SerenEngine
{
	class SEREN_API KeyboardInput
	{
	public:
		virtual ~KeyboardInput() = default;

		FORCE_INLINE int8_t GetValue(EKeyCode keyCode) const { return (IsPressed(keyCode) || IsHeld(keyCode)) ? 1 : 0; }
		FORCE_INLINE EKeyState GetState(EKeyCode keyCode) { return GetState((int32_t)keyCode); }
		FORCE_INLINE bool IsPressed(EKeyCode keyCode) const { return IsPressed((int32_t)keyCode); }
		FORCE_INLINE bool IsHeld(EKeyCode keyCode) const { return IsHeld((int32_t)keyCode); }
		FORCE_INLINE bool IsReleased(EKeyCode keyCode) const { return IsReleased((int32_t)keyCode); }

		virtual EKeyState GetState(int32_t keyCode) const = 0;
		virtual bool IsPressed(int32_t keyCode) const = 0;
		virtual bool IsHeld(int32_t keyCode) const = 0;
		virtual bool IsReleased(int32_t keyCode) const = 0;
	protected:
		KeyboardInput() = default;
	};

	class SEREN_API GLFWKeyboardInput : public KeyboardInput
	{
	public:
		virtual EKeyState GetState(int32_t keyCode) const override;
		virtual bool IsPressed(int32_t keyCode) const override;
		virtual bool IsHeld(int32_t keyCode) const override;
		virtual bool IsReleased(int32_t keyCode) const override;
		GLFWKeyboardInput(void* window);
	private:
		GLFWwindow* m_Window;
	};
	class SEREN_API MouseInput
	{
	public:
		virtual ~MouseInput() = default;

		FORCE_INLINE int8_t GetValue(EMouseButton button) const { return (IsPressed(button) || IsHeld(button)) ? 1 : 0; }
		FORCE_INLINE EKeyState GetState(EMouseButton button) { return GetState((int32_t)button); }
		FORCE_INLINE bool IsPressed(EMouseButton button) const { return IsPressed((int32_t)button); }
		FORCE_INLINE bool IsHeld(EMouseButton button) const { return IsHeld((int32_t)button); }
		FORCE_INLINE bool IsReleased(EMouseButton button) const { return IsReleased((int32_t)button); }

		virtual EKeyState GetState(int32_t button) const = 0;
		virtual bool IsPressed(int32_t button) const = 0;
		virtual bool IsHeld(int32_t button) const = 0;
		virtual bool IsReleased(int32_t button) const = 0;

		FORCE_INLINE float GetPositionX() const { return mX; }
		FORCE_INLINE float GetPositionY() const { return mY; }
		FORCE_INLINE float GetOffsetX() const { return mOffsetX; }
		FORCE_INLINE float GetOffsetY() const { return mOffsetY; }
		FORCE_INLINE float GetScrollX() const { return mScrollX; }
		FORCE_INLINE float GetScrollY() const { return mScrollY; }

		FORCE_INLINE void SetPosition(float x, float y) { mX = x; mY = y; }
		FORCE_INLINE void SetPositionX(float x) { mX = x; }
		FORCE_INLINE void SetPositionY(float y) { mY = y; }

		FORCE_INLINE void SetOffset(float offsetX, float offsetY) { mOffsetX = offsetX; mOffsetY = offsetY; }
		FORCE_INLINE void SetOffsetX(float offsetX) { mOffsetX = offsetX; }
		FORCE_INLINE void SetOffsetY(float offsetY) { mOffsetY = offsetY; }

		FORCE_INLINE void SetScroll(float scrollX, float scrollY) { mScrollX = scrollX; mScrollY = scrollY; }
		FORCE_INLINE void SetScrollX(float scrollX) { mScrollX = scrollX; }
		FORCE_INLINE void SetScrollY(float scrollY) { mScrollY = scrollY; }
	protected:
		MouseInput() = default;
	protected:
		float mX, mY;
		float mOffsetX, mOffsetY;
		float mScrollX, mScrollY;
	};
	class SEREN_API GLFWMouseInput : public MouseInput {
	public:
		GLFWMouseInput(void* window);
		virtual EKeyState GetState(int32_t button) const override;
		virtual bool IsPressed(int32_t button) const override;
		virtual bool IsHeld(int32_t button) const override;
		virtual bool IsReleased(int32_t button) const override;
	private:
		GLFWwindow* m_Window;
	};

	struct SEREN_API InputState {
		KeyboardInput* Keyboard;
		MouseInput* Mouse;
	};
}