#pragma once 

#include"pch.h"
#include"Renderer/RendererAPI.h"

namespace SerenEngine {
	class OpenGLFactory {
	public:
		static uint32_t ToOpenGLMode(ERendererMode mode);
		static uint32_t ToOpenGLPrimitive(ERendererPrimitive primitive);
		static uint32_t ToOpenGLState(ERendererState renderState);
		static uint32_t ToOpenGLBlendFunction(ERendererBlendFunction function);
		static uint32_t ToOpenGLBlendEquation(ERendererBlendEquation equation);
	};
}