#include"VertexBuffer.h"
#include"ResourceManager.h"

namespace SerenEngine {
	DEFINE_RTTI(VertexBuffer, Object::RunTimeType)

	VertexBuffer* VertexBuffer::Create() {
		return ResourceManager::Get().NewVertexBuffer();
	}
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		return ResourceManager::Get().NewVertexBuffer(vertices,size);
	}
}