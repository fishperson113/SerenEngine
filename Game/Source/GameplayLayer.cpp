#include"GameplayLayer.h"
#include<SerenEngine/Base.h>
#include<ECS/System/System.h>
#include<Renderer/RenderCommand.h>
#include<Resource/Buffer.h>
#include<Renderer/Renderer.h>
using namespace SerenEngine;
GameplayLayer::GameplayLayer() : m_CameraController(1280.0f / 720.0f) {
	LOG_TRACE("GameplayLayer is created");
	m_CameraController.GetCamera().SetViewportSize(1280.0f, 720.0f);
}
void GameplayLayer::OnAttach() {
	/*LOG_TRACE("GameplayLayer is attached");

	MemoryManager* memoryManager = new MemoryManager();
	{
		SerenEngine::ECS::Coordinator* coordinator = memoryManager->NewOnStack<SerenEngine::ECS::Coordinator>("Coordinator");
		SerenEngine::Actor* actor = memoryManager->NewOnStack<SerenEngine::Actor>(SerenEngine::Actor::RunTimeType.GetTypeName(), coordinator);
		actor->AddComponent<SerenEngine::TransformComponent>(2.0f, 3.0f);
		SerenEngine::TransformComponent& transform = actor->GetComponent<SerenEngine::TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetX(), transform.GetY());

		transform.SetX(10.0f);
		transform.SetY(-20.0f);
		transform = actor->GetComponent<TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetX(), transform.GetY());

		if (actor->HasComponent<TransformComponent>()) {
			actor->RemoveComponent<TransformComponent>();
		}

		if (!actor->HasComponent<TransformComponent>()) {
			LOG_WARN("Actor transform component has been removed");
		}
		memoryManager->FreeOnStack(actor);
		memoryManager->FreeOnStack(coordinator);
		coordinator->~Coordinator();
	}
	memoryManager->ClearOnStack();*/
	
	mRenderer = Application::Get().GetRenderer();
}
void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}
void GameplayLayer::OnUpdate(Time time) {
	m_CameraController.OnUpdate(time.GetDeltaTime());
	mRenderer->BeginScene(m_CameraController.GetCamera());
	RenderCommand::SetClearColor(1.0f, 0.3f, 0.6f);
	float angle=(27*3.14)/180.0f;
	Renderer::DrawRotatedQuad(glm::vec3(0.0f, 0.0f, 0.0f),
					   glm::vec2(1.0f, 1.0f),
						angle,
					   glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	Renderer::DrawRotatedQuad(glm::vec3(2.0f, 0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		angle,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Renderer::DrawCircle(glm::vec2(2.0f, 1.0f), 1, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Renderer::DrawLine(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),200);

	Renderer::DrawLine(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 3.0f, 1.0f), 200);
	mRenderer->EndScene();

}
bool GameplayLayer::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
	return false;
}

void GameplayLayer::OnProcessInput(const InputState& input)
{
	m_CameraController.OnProcessInput(input);
}

bool GameplayLayer::OnWindowResizedEvent(const SerenEngine::WindowResizedEvent& e)
{
	m_CameraController.OnWindowResizedEvent(e);
	return false;
}

bool GameplayLayer::OnMouseScrolledEvent(const SerenEngine::MouseScrolledEvent& e)
{
	m_CameraController.OnMouseScrolledEvent(e);
	return false;
}
