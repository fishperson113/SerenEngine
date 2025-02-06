#pragma once
#include <Core/Layer/Layer.h>
#include<Resource/VertexBuffer.h>
#include<Resource/IndexBuffer.h>
#include<Resource/Shader.h>
#include<Resource/VertexArray.h>
class GameplayLayer : public SerenEngine::Layer
{
public:
	GameplayLayer() {}
	~GameplayLayer() {}
private:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(SerenEngine::Time time);
	virtual bool OnKeyPressedEvent(const SerenEngine::KeyPressedEvent& eventContext);
private:
	SerenEngine::VertexArray* mFirstQuad;
	SerenEngine::VertexArray* mSecondQuad;
	SerenEngine::Shader* mShader;
};