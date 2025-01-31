#pragma once
#include"pch.h"
#include"ECS/Coordinator.h"
#include"Object.h"
namespace SerenEngine {
	class SEREN_API Actor : public Object {
	public:
		DECLARE_RTTI
	public:
		Actor() = default;
		Actor(ECS::Coordinator* coordinator);
		Actor(ECS::EntityID id, ECS::Coordinator* coordinator);
		~Actor();
		template<typename T, typename... Args>
		FORCE_INLINE T& AddComponent(Args&&... args) { return mCoordinator->AddComponent<T>(mID, mCoordinator, std::forward<Args>(args)...); }

		template<typename T>
		FORCE_INLINE T& GetComponent() { return mCoordinator->GetComponent<T>(mID); }

		template<typename T>
		FORCE_INLINE bool HasComponent() { return mCoordinator->HasComponent<T>(mID); }

		template<typename T>
		FORCE_INLINE void RemoveComponent() { mCoordinator->RemoveComponent<T>(mID); }
		FORCE_INLINE ECS::EntityID GetID() const { return mID; }
	private:
		ECS::EntityID mID;
		ECS::Coordinator* mCoordinator;
	};
}