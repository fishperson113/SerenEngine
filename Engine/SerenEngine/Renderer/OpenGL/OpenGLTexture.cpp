﻿#include "OpenGLTexture.h"
#include "pch.h"
#include <glad/gl.h>
#include "Renderer/Renderer.h"

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
    {
        // TODO:
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
