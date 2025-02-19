#pragma once
#include"Resource/Texture.h"
namespace SerenEngine {
	class OpenGLTexture : public Texture {
	public:
		DECLARE_RTTI
	public:
		OpenGLTexture();
		OpenGLTexture(uint32_t width, uint32_t height);
		OpenGLTexture(const std::string& path);
		~OpenGLTexture();
		virtual void Release() override;
		virtual void Bind(uint32_t slot = 0) override;
		virtual void Unbind() override;
		virtual void SetData(void* data, uint32_t size) override;

		FORCE_INLINE virtual uint32_t GetID() const override { return mID; }
		FORCE_INLINE virtual uint32_t GetWidth() const override { return mWidth; }
		FORCE_INLINE virtual uint32_t GetHeight() const override { return mHeight; }
		FORCE_INLINE virtual uint32_t GetChannels() const override { return mChannels; }
		FORCE_INLINE virtual void SetID(uint32_t id) override { mID = id; }
		FORCE_INLINE virtual void SetWidth(uint32_t width) override { mWidth = width; }
		FORCE_INLINE virtual void SetHeight(uint32_t height) override { mHeight = height; }
		FORCE_INLINE virtual void SetChannels(uint32_t channels) override { mChannels = channels; }
	private:
		uint32_t mID, mWidth, mHeight, mChannels;
		std::string m_Path;
		GLenum m_InternalFormat, m_DataFormat;
	};
}