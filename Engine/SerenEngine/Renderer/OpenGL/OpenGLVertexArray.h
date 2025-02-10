#pragma once

#include"Resource/VertexArray.h"

namespace SerenEngine {
	class VertexBuffer;
	class IndexBuffer;
	class SEREN_API OpenGLVertexArray : public VertexArray {
	public:
		DECLARE_RTTI
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		FORCE_INLINE virtual class VertexBuffer* GetVertexBuffer() override { return mVertexBuffer; }
		FORCE_INLINE virtual class IndexBuffer* GetIndexBuffer() override { return mIndexBuffer; }
		FORCE_INLINE virtual const std::vector<VertexBuffer*> GetVertexBuffers() const override { return m_VertexBuffers; };

		virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) override;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) override;
		virtual void SetIndexBuffer(void* data, uint32_t size, uint32_t nums, ERendererMode mode = ERendererMode::Static) override;

		virtual void Release() override;
		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		uint32_t mID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<VertexBuffer*> m_VertexBuffers;
		VertexBuffer* mVertexBuffer;
		IndexBuffer* mIndexBuffer;
	};
}