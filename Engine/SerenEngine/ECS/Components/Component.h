#pragma once
#include"ECS/Type/Actor.h"
#include"ECS/IComponent.h"
namespace SerenEngine {
	class TransformComponent : public ECS::Component<TransformComponent, Actor> {
		DECLARE_RTTI
	public:
		TransformComponent() = default;
		TransformComponent(float x, float y) : mX(x), mY(y) {}
		~TransformComponent() {}
		float GetX() const { return mX; }
		void SetX(float value) { mX = value; }
		float GetY() const { return mY; }
		void SetY(float value) { mY = value; }
	private:
		float mX, mY;
	};
	DEFINE_RTTI_NO_PARENT(TransformComponent)
	
		//TODO: add more components
}