#include"OpenGLIndexBuffer.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"

#include<glad/gl.h>

namespace SerenEngine {
	DEFINE_RTTI(OpenGLIndexBuffer, IndexBuffer::RunTimeType)

		OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t nums) : mNums(nums)
	{
		glGenBuffers(1, &mID);
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glBufferData(GL_ARRAY_BUFFER, nums * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		Release();
	}

	void OpenGLIndexBuffer::Release()
	{
		glDeleteBuffers(1, &mID);
		ResourceManager::Get().FreeIndexBuffer(this);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}