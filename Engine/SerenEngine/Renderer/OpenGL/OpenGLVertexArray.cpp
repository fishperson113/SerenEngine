#include"OpenGLVertexArray.h"
#include"Resource/VertexBuffer.h"
#include"Resource/IndexBuffer.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"
#include"Core/Logger/Logger.h"
#include<glad/gl.h>

namespace SerenEngine {
	DEFINE_RTTI(OpenGLVertexArray, VertexArray::RunTimeType)
		static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	//	OpenGLVertexArray::OpenGLVertexArray() :
	//	mID(), mVertexBuffer(VertexBuffer::Create()), mIndexBuffer(IndexBuffer::Create())
	//{
	//	Renderer::Submit([this]() {
	//		glGenVertexArrays(1, &mID);
	//		glBindVertexArray(mID);
	//		// Vertex Buffer
	//		uint32_t vertexBufferID;
	//		glGenBuffers(1, &vertexBufferID);
	//		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	//		glEnableVertexAttribArray(0);
	//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	//		glEnableVertexAttribArray(1);
	//		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	//		glEnableVertexAttribArray(2);
	//		mVertexBuffer->SetID(vertexBufferID);
	//		// Index Buffer
	//		uint32_t indexBufferID;
	//		glGenBuffers(1, &indexBufferID);
	//		mIndexBuffer->SetID(indexBufferID);
	//		});
	//}
	OpenGLVertexArray::OpenGLVertexArray() : mID(0), m_VertexBufferIndex(0), mIndexBuffer(nullptr), mVertexBuffer(nullptr)
	{
		glGenVertexArrays(1, &mID);
	}
	OpenGLVertexArray::~OpenGLVertexArray() {
		
	}

	void OpenGLVertexArray::AddVertexBuffer(VertexBuffer* vertexBuffer)
	{
		ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		m_VertexBuffers.push_back(vertexBuffer);

		glBindVertexArray(mID);
		vertexBuffer->Bind();
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			m_VertexBufferIndex++;
		}
	}

	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
	{
		mIndexBuffer = indexBuffer;
		glBindVertexArray(mID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer->GetID());
	}

	void OpenGLVertexArray::Release()
	{
		glDeleteVertexArrays(1, &mID);
		ResourceManager::Get().FreeVertexArray(this);
		mVertexBuffer->Release();
		mIndexBuffer->Release();
	}

	void OpenGLVertexArray::SetIndexBuffer(void* data, uint32_t size, uint32_t nums, ERendererMode mode)
	{
		mIndexBuffer->SetSize(size);
		mIndexBuffer->SetNums(nums);

		void* submitData = ResourceManager::Get().AllocatePerFrame(size, alignof(uint32_t));
		memcpy(submitData, data, size);
		glBindVertexArray(mID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer->GetID());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer->GetSize(), submitData, OpenGLFactory::ToOpenGLMode(mode));
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(mID);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
}