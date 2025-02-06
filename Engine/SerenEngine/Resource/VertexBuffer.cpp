#include"VertexBuffer.h"
#include"ResourceManager.h"

namespace SerenEngine {
	DEFINE_RTTI(VertexBuffer, Object::RunTimeType)

	VertexBuffer* VertexBuffer::Create() {
		return ResourceManager::Get().NewVertexBuffer();
	}
}