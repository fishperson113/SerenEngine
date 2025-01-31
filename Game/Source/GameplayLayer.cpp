#include"GameplayLayer.h"
#include<SerenEngine/Base.h>
#include<Core/System/System.h>
using namespace SerenEngine;

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	MemoryManager* memoryManager = new MemoryManager();
	{
		auto systemManager = memoryManager->NewOnStack<SerenEngine::ECS::SystemManager>("SystemManager");
		auto& collisionSystem = systemManager->AddSystem<SerenEngine::CollisionResolver>();
		auto& animationSystem = systemManager->AddSystem<SerenEngine::AnimationSystem>();
		auto& renderer2D = systemManager->AddSystem<SerenEngine::Renderer2D>();

		systemManager->AddSystemDependency(&animationSystem, &collisionSystem);
		systemManager->AddSystemDependency(&renderer2D, &collisionSystem, &animationSystem);
		systemManager->OnInit();
		systemManager->OnUpdate(0.0f);
		systemManager->OnShutdown();
		memoryManager->FreeOnStack(systemManager);
	}
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
	}
	memoryManager->ClearOnStack();
}
void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}
void GameplayLayer::OnUpdate(Time time) {

}
bool GameplayLayer::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
	return false;
}