#pragma once

#include"Core/Type/Object.h"
#include"Renderer/RendererAPI.h"
#include<glm/glm.hpp>
#include"Resource/Buffer.h"
namespace SerenEngine {
	struct SEREN_API Vertex {
		glm::vec3 Position;
		glm::vec2 TexCoords;
		glm::vec4 Color;
	};

	class SEREN_API VertexBuffer : public Object {
	public:
		DECLARE_RTTI
	public:
		static VertexBuffer* Create();
		static VertexBuffer* Create(float* vertices, uint32_t size);
	public:
		virtual ~VertexBuffer() = default;
		virtual void Release() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetID() const = 0;
		virtual uint32_t GetSize() const = 0;
		virtual void SetID(uint32_t id) = 0;
		virtual void SetSize(uint32_t size) = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
	protected:
		VertexBuffer() = default;
	};
}