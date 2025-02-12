#pragma once

#include"Resource/VertexBuffer.h"
namespace SerenEngine {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		DECLARE_RTTI
	public:
		OpenGLVertexBuffer();
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		virtual void Release() override;
		virtual void Bind() override;
		virtual void Unbind() override;

		FORCE_INLINE virtual uint32_t GetID() const override { return mID; }
		FORCE_INLINE virtual uint32_t GetSize() const override { return mSize; }
		FORCE_INLINE virtual void SetID(uint32_t id) override { mID = id; }
		FORCE_INLINE virtual void SetSize(uint32_t size) override { mSize = size; }
		FORCE_INLINE virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		FORCE_INLINE virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual void SetData(const void* data, uint32_t size) override;
	private:
		uint32_t mID, mSize;
		void* mData;
		ERendererMode mMode;
		BufferLayout m_Layout;
	};
}