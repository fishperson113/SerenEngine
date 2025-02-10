#pragma once


#include "pch.h"
#include"Core/Type/Object.h"
#include"Renderer/RendererAPI.h"

namespace SerenEngine {

	class SEREN_API Texture : public Object
	{
	public:
		DECLARE_RTTI
	public:
		static Texture* Create(const char* path);
		static Texture* Create(uint32_t width, uint32_t height);
	public:
		virtual ~Texture() = default;
		virtual void Release() =0;
		virtual void Bind(uint32_t slot = 0) = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetID() const = 0;
		virtual uint32_t GetChannels() const = 0;
		
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void SetID(uint32_t id) = 0;
		virtual void SetWidth(uint32_t width) = 0;
		virtual void SetHeight(uint32_t height) = 0;
		virtual void SetChannels(uint32_t channels) = 0;
	};

}