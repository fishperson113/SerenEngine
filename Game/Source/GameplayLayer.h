#pragma once
#include <Core/Layer/Layer.h>
#include<Resource/VertexBuffer.h>
#include<Resource/IndexBuffer.h>
#include<Resource/Shader.h>
#include<Resource/VertexArray.h>
#include<Renderer/OrthographicCameraController.h>
#include"pch.h"
#include"Renderer/Renderer.h"
class GameplayLayer : public SerenEngine::Layer
{
public:
	GameplayLayer();
	~GameplayLayer() {};
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(SerenEngine::Time time) override;
	virtual bool OnKeyPressedEvent(const SerenEngine::KeyPressedEvent& eventContext);
	virtual void OnProcessInput(const SerenEngine::InputState&) override;
	virtual bool OnWindowResizedEvent(const SerenEngine::WindowResizedEvent&) override;
	virtual bool OnMouseScrolledEvent(const SerenEngine::MouseScrolledEvent&) override;
private:
	SerenEngine::Renderer* mRenderer;
	SerenEngine::OrthographicCameraController m_CameraController;
};