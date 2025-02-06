#include"VertexArray.h"
#include"ResourceManager.h"

namespace SerenEngine {
	DEFINE_RTTI(VertexArray, Object::RunTimeType)

		VertexArray* VertexArray::Create() {
		return ResourceManager::Get().NewVertexArray();
	}
}
