#include"OpenGLVertexBuffer.h"

#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"
#include<glad/gl.h>

namespace SerenEngine {
	DEFINE_RTTI(OpenGLVertexBuffer, VertexBuffer::RunTimeType)
	OpenGLVertexBuffer::OpenGLVertexBuffer()
		: mID(0), mSize(0), mData(nullptr), mMode(ERendererMode::Static), m_Layout()
	{
		glGenBuffers(1, &mID);
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glBufferData(GL_ARRAY_BUFFER, 0, nullptr, OpenGLFactory::ToOpenGLMode(mMode));
	}
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size){
		glGenBuffers(1, &mID);
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		Release();
	}

	void OpenGLVertexBuffer::Release() {
		glDeleteBuffers(1, &mID);
		ResourceManager::Get().FreeVertexBuffer(this);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mID);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}