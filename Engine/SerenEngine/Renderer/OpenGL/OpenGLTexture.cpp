#include "OpenGLTexture.h"
#include "pch.h"
#include <glad/gl.h>
#include "Renderer/Renderer.h"
#include "stb_image.h"
namespace SerenEngine {

    DEFINE_RTTI(OpenGLTexture, Texture::RunTimeType)

        OpenGLTexture::OpenGLTexture()
        : mID(0), mWidth(0), mHeight(0), m_InternalFormat(GL_RGBA8), m_DataFormat(GL_RGBA)
    {
    }

    OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height)
        : mWidth(width), mHeight(height), m_InternalFormat(GL_RGBA8), m_DataFormat(GL_RGBA)
    {
        glGenTextures(1, &mID);
        glBindTexture(GL_TEXTURE_2D, mID);

        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_DataFormat, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture::OpenGLTexture(const std::string& path)
        : m_Path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        mWidth = width;
        mHeight = height;
		mChannels = channels;
        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;

        glGenTextures(1, &mID);
        glBindTexture(GL_TEXTURE_2D, mID);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindTexture(GL_TEXTURE_2D, 0); 

        stbi_image_free(data);

    }

    OpenGLTexture::~OpenGLTexture()
    {
        Release();
    }

    void OpenGLTexture::Release()
    {
        if (mID)
        {
            glDeleteTextures(1, &mID);
            mID = 0;
        }
    }

    void OpenGLTexture::Bind(uint32_t slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, mID);
    }

    void OpenGLTexture::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture::SetData(void* data, uint32_t size)
    {
        glBindTexture(GL_TEXTURE_2D, mID);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, m_DataFormat, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
