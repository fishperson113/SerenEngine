#include"GameplayLayer.h"
#include<SerenEngine/Base.h>
#include<ECS/System/System.h>
#include<Renderer/Renderer.h>
using namespace SerenEngine;
GameplayLayer::GameplayLayer() : m_CameraController(720.0f / 720.0f) {
	LOG_TRACE("GameplayLayer is created");
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
	mFirstQuad = VertexArray::Create();
	mSecondQuad = VertexArray::Create();
	mShader = Shader::Create("Assets/Shader/quad.glsl");

	Vertex vertices[4] = {
		{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // top-left
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // bottom-left
		{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // bottom-right
		{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)} // top-right
	};
	uint32_t indicies[6] = {
		0, 1, 2, // left-bottom triangle
		2, 3, 0 // right-top triangle
	};
	mFirstQuad->SetVertexBuffer(vertices, sizeof(vertices));
	mFirstQuad->SetIndexBuffer(indicies, sizeof(indicies), sizeof(indicies) / sizeof(uint32_t));

	Vertex quadVertices[4] = {
		{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)}, // top-left
		{glm::vec3(0.0f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // bottom-left
		{glm::vec3(1.0f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)}, // bottom-right
		{glm::vec3(1.0f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)} // top-right
	};
	mSecondQuad->SetVertexBuffer(quadVertices, sizeof(quadVertices));
	mSecondQuad->SetIndexBuffer(indicies, sizeof(indicies), sizeof(indicies) / sizeof(uint32_t));
}
void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}
void GameplayLayer::OnUpdate(Time time) {
	m_CameraController.OnUpdate(time.GetDeltaTime());
	SerenEngine::Renderer::SetClearColor(1.0f, 0.3f, 0.6f);

	mShader->Bind();
	
	mShader->SetVector3("tempColor", glm::vec3(1.0f));
	mShader->SetFloat("alpha", 0.5f);
	mShader->SetMatrix4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());

	mFirstQuad->Bind();
	Renderer::DrawIndexed(mFirstQuad,mFirstQuad->GetIndexBuffer()->GetNums());

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
