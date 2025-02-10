#pragma once

#include"Resource/IndexBuffer.h"

namespace SerenEngine {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		DECLARE_RTTI
	public:
		OpenGLIndexBuffer()
			: mID(0), mSize(0), mNums(0)
		{}
		OpenGLIndexBuffer(uint32_t* indices, uint32_t nums);
		~OpenGLIndexBuffer();
		virtual void Release() override;
		virtual void Bind() override;
		virtual void Unbind() override;
		FORCE_INLINE virtual uint32_t GetID() const override { return mID; }
		FORCE_INLINE virtual uint32_t GetSize() const override { return mSize; }
		FORCE_INLINE virtual uint32_t GetNums() const override { return mNums; }
		virtual void SetID(uint32_t id) override { mID = id; }
		virtual void SetSize(uint32_t size) override { mSize = size; }
		virtual void SetNums(uint32_t nums) override { mNums = nums; }
	private:
		uint32_t mID, mSize, mNums;
	};
}