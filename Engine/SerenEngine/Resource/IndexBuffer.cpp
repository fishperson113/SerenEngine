#include"IndexBuffer.h"
#include"ResourceManager.h"

namespace SerenEngine {
	DEFINE_RTTI(IndexBuffer, Object::RunTimeType)

	IndexBuffer* IndexBuffer::Create() {
		return ResourceManager::Get().NewIndexBuffer();
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t nums)
	{
		return ResourceManager::Get().NewIndexBuffer(indices,nums);
	}
}