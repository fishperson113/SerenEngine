#pragma once

#include"Core/Type/RTTI.h"
#include"Resource/ResourceManager.h"
#include"Memory/MemoryChunkManager.h"
#include"OpenGLVertexBuffer.h"
#include"OpenGLIndexBuffer.h"
#include"OpenGLShader.h"
#include"OpenGLVertexArray.h"
#include"OpenGLTexture.h"
namespace SerenEngine {
	class OpenGLResourceManager : public ResourceManager {
	public:
		DECLARE_RTTI

	public:
		OpenGLResourceManager();
		~OpenGLResourceManager();

		virtual void OnReset() override;
		//VertexArray
		virtual VertexArray* NewVertexArray() override;
		virtual void FreeVertexArray(VertexArray* memory) override;
		//VertexBuffer
		virtual class VertexBuffer* NewVertexBuffer() override;
		virtual class VertexBuffer* NewVertexBuffer(float* vertices, uint32_t size) override;
		virtual void FreeVertexBuffer(void* memory) override;
		//IndexBuffer
		virtual class IndexBuffer* NewIndexBuffer() override;
		virtual class IndexBuffer* NewIndexBuffer(uint32_t* indices, uint32_t nums) override;
		virtual void FreeIndexBuffer(void* memory) override;
		//Shader
		virtual class Shader* NewShader(const char* filepath) override;
		virtual void FreeShader(void* memory) override;
		//Texture
		virtual class Texture* NewTexture(const char* filepath) override;
		virtual class Texture* NewTexture(uint32_t width, uint32_t height) override;
		virtual void FreeTexture(void* memory) override;

		virtual void* AllocatePerFrame(uint32_t size, uint8_t alignment) override;
	private:
		std::unordered_map<std::string, std::string> ParseGLSL(const char* shaderSource);
		std::string ReadFromFile(const char* filepath);
	private:
		MemoryManager mGeneralMemoryManager;
		MemoryChunkManager<OpenGLTexture, 100> mTextureMemoryManager;
		MemoryChunkManager<OpenGLVertexBuffer, 100> mVertexBufferMemoryManager;
		MemoryChunkManager<OpenGLIndexBuffer, 100> mIndexBufferMemoryManager;
		MemoryChunkManager<OpenGLShader, 100> mShaderMemoryManager;
		MemoryChunkManager<OpenGLVertexArray, 100> mVertexArrayMemoryManager;
		std::unordered_map<const char*, OpenGLShader*> mShaderMap;
	};
}