#include"OpenGLFactory.h"

#include<glad/gl.h>

namespace SerenEngine {
	uint32_t OpenGLFactory::ToOpenGLMode(ERendererMode mode) {
		if (mode == ERendererMode::Dynamic) return GL_DYNAMIC_DRAW;
		if (mode == ERendererMode::Stream) return GL_STREAM_DRAW;

		return GL_STATIC_DRAW;
	}

	uint32_t OpenGLFactory::ToOpenGLPrimitive(ERendererPrimitive primitive) {
		if (primitive == ERendererPrimitive::Points) return GL_POINTS;
		if (primitive == ERendererPrimitive::Lines) return GL_LINES;
	
		return GL_TRIANGLES;
	}
	uint32_t OpenGLFactory::ToOpenGLState(ERendererState renderState) {
		if (renderState == ERendererState::DepthTesting) return GL_DEPTH_TEST;
		if (renderState == ERendererState::StencilTesting) return GL_STENCIL_TEST;
		if (renderState == ERendererState::FaceCulling) return GL_CULL_FACE;
		if (renderState == ERendererState::MultiSample) return GL_MULTISAMPLE;

		return GL_BLEND;
	}

	uint32_t OpenGLFactory::ToOpenGLBlendFunction(ERendererBlendFunction function)
	{
		if (function == ERendererBlendFunction::One) return GL_ONE;
		if (function == ERendererBlendFunction::SourceAlpha) return GL_SRC_ALPHA;
		if (function == ERendererBlendFunction::OneMinusSourceAlpha) return GL_ONE_MINUS_SRC_ALPHA;
		if (function == ERendererBlendFunction::DestinationAlpha) return GL_DST_ALPHA;
		if (function == ERendererBlendFunction::OneMinusDestionaAlpha) return GL_ONE_MINUS_DST_ALPHA;

		return GL_ZERO;
	}

	uint32_t OpenGLFactory::ToOpenGLBlendEquation(ERendererBlendEquation equation)
	{
		if (equation == ERendererBlendEquation::Subtract) return GL_FUNC_SUBTRACT;
		if (equation == ERendererBlendEquation::ReverseSubtract) return GL_FUNC_REVERSE_SUBTRACT;
		if (equation == ERendererBlendEquation::Min) return GL_MIN;
		if (equation == ERendererBlendEquation::Max) return GL_MAX;

		return GL_FUNC_ADD;
	}
}