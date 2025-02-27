#include"Renderer/RenderCommand.h"
#include"OpenGLFactory.h"
#include"Core/Logger/Logger.h"
#include"Resource/IndexBuffer.h"
#include"Renderer/Renderer.h"
#define GLAD_GL_IMPLEMENTATION
#include<glad/gl.h>
namespace SerenEngine {
	DEFINE_RTTI_NO_PARENT(OpenGLRenderCommand)

	OpenGLRenderCommand::OpenGLRenderCommand() : mRenderData() {

	}

	OpenGLRenderCommand::~OpenGLRenderCommand() {
	}

	void OpenGLRenderCommand::SetLineWidthImpl(float width)
	{
		glLineWidth(width);
	}

	void OpenGLRenderCommand::DrawLinesImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset)
	{
		glDrawArrays(OpenGLFactory::ToOpenGLPrimitive(primitive), offset, nums);

	}

	void OpenGLRenderCommand::DrawIndexedImpl(const Shared<VertexArray>& vertexArray, uint32_t indexCount, ERendererPrimitive primitive, uint32_t offset)
	{
		vertexArray->Bind();

		glDrawElements(OpenGLFactory::ToOpenGLPrimitive(primitive),
			indexCount,
			GL_UNSIGNED_INT,
			(const void*)(intptr_t)offset);
	}

	void OpenGLRenderCommand::DrawIndexedImpl(VertexArray* vertexArray, uint32_t indexCount, ERendererPrimitive primitive, uint32_t offset)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetNums();
		vertexArray->Bind();
		DrawIndexedImpl(count, primitive,offset);
	}

	void OpenGLRenderCommand::SetClearColorImpl(float r, float g, float b, float w) {
		glClearColor(r, g, b, w);
	}
	void OpenGLRenderCommand::ClearImpl() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRenderCommand::DrawIndexedImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) {
		glDrawElements(OpenGLFactory::ToOpenGLPrimitive(primitive), nums, GL_UNSIGNED_INT, (void*)offset);
	}
	void OpenGLRenderCommand::DrawLinesImpl(VertexArray* vertexArray, uint32_t vertexCount)
	{
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}
	void OpenGLRenderCommand::EnableBlendingImpl(ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) {
		if (mRenderData.EnableRendererState != ERendererState::Blending) {
			glEnable(OpenGLFactory::ToOpenGLState(ERendererState::Blending));
			mRenderData.EnableRendererState = ERendererState::Blending;
		}

		if (mRenderData.BlendEquation != blendEquation) {
			glBlendEquation(OpenGLFactory::ToOpenGLBlendEquation(blendEquation));
			mRenderData.BlendEquation = blendEquation;
		}

		if (mRenderData.BlendSource != source || mRenderData.BlendDestination != destination) {
			glBlendFunc(OpenGLFactory::ToOpenGLBlendFunction(source), OpenGLFactory::ToOpenGLBlendFunction(destination));
			mRenderData.BlendSource = source;
			mRenderData.BlendDestination = destination;
		}
	}

	void OpenGLRenderCommand::DisableBlendingImpl() {
		if (mRenderData.DisableRendererState == ERendererState::Blending) return;

		glDisable(OpenGLFactory::ToOpenGLState(ERendererState::Blending));
		mRenderData.DisableRendererState = ERendererState::Blending;
	}
	void OpenGLRenderCommand::SetViewportImpl(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}
}