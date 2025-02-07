#include"GameplayLayer.h"
#include<SerenEngine/Base.h>
#include<Core/System/System.h>
#include<Renderer/Renderer.h>
using namespace SerenEngine;

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
	SerenEngine::Renderer::SetClearColor(1.0f, 0.3f, 0.6f);
	static float temp = 0.0f;
	temp += time.GetDeltaTime();

	Renderer::EnableBlending();

	mShader->Bind();
	/*mShader->SetVector3("tempColor", glm::vec3(glm::cos(temp) + 1.0f, 1.0f, glm::sin(temp) + 1.0f));
	mShader->SetFloat("alpha", glm::sin(temp) + 1.0f);
	*/
	mShader->SetVector3("tempColor", glm::vec3(1.0f));
	mShader->SetFloat("alpha", 0.5f);
	mFirstQuad->Bind();
	Renderer::DrawIndexed(mFirstQuad->GetIndexBuffer()->GetNums());

	mSecondQuad->Bind();
	Renderer::DrawIndexed(mSecondQuad->GetIndexBuffer()->GetNums());
}
bool GameplayLayer::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
	return false;
}