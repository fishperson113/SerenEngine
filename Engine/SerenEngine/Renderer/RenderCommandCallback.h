#pragma once
#include"pch.h"
namespace SerenEngine {
	using RenderCallback = std::function<void()>;

	class RenderCommandCallback {
	public:
		RenderCommandCallback();
		RenderCommandCallback(const RenderCallback&);
		~RenderCommandCallback();
		void Execute();
		FORCE_INLINE uint32_t GetFrameIndex() const { return mFrameIndex; }
		FORCE_INLINE void SetFrameIndex(uint32_t frameIndex) { mFrameIndex = frameIndex; }
	private:
		RenderCallback mCallback;
		uint32_t mFrameIndex;
	};
}