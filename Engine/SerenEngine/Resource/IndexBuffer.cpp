#include"IndexBuffer.h"
#include"ResourceManager.h"

namespace SerenEngine {
	DEFINE_RTTI(IndexBuffer, Object::RunTimeType)

	IndexBuffer* IndexBuffer::Create() {
		return ResourceManager::Get().NewIndexBuffer();
	}
}