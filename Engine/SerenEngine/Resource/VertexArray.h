#pragma once

#include"pch.h"
#include"Core/Type/Object.h"
#include"Renderer/RendererAPI.h"

namespace SerenEngine {
	class SEREN_API VertexArray : public Object {
	public:
		DECLARE_RTTI
	public:
		static VertexArray* Create();
	public:
		virtual ~VertexArray() = default;
		virtual class VertexBuffer* GetVertexBuffer() = 0;
		virtual class IndexBuffer* GetIndexBuffer() = 0;
		virtual const std::vector<VertexBuffer*> GetVertexBuffers() const = 0;
		
		virtual void Release() = 0;
		virtual void SetIndexBuffer(void* data, uint32_t size, uint32_t nums, ERendererMode mode = ERendererMode::Static) = 0;

		virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0;


		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	protected:
		VertexArray() = default;
	};
}