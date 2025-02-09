#pragma once
#include"ECS/ISystem.h"
#include"Core/Logger/Logger.h"
#include"Core/Time/Time.h"
#include"Core/Type/RTTI.h"
#include "glm/glm.hpp"
namespace SerenEngine {
	class CollisionResolver : public ECS::System<CollisionResolver> {
	public:
		DECLARE_RTTI
	public:
		CollisionResolver() = default;
		CollisionResolver(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low) : System(id, priority) {}
		~CollisionResolver() = default;
		virtual void OnInit() override {
			CORE_LOG_INFO("CollisionResolver init!");
		}
		virtual void OnUpdate(Time time) override {
			CORE_LOG_INFO("CollisionResolver update!");
		}
		virtual void OnShutdown() override {
			CORE_LOG_INFO("CollisionResolver is shutdown!");
		}
	};
	class AnimationSystem : public ECS::System<AnimationSystem> {
	public:
		DECLARE_RTTI
	public:
		AnimationSystem() = default;
		AnimationSystem(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low) : System(id, priority) {}
		~AnimationSystem() = default;
		virtual void OnInit() override {
			CORE_LOG_INFO("AnimationSystem init!");
		}
		virtual void OnUpdate(Time time) override {
			CORE_LOG_INFO("AnimationSystem update!");
		}
		virtual void OnShutdown() override {
			CORE_LOG_INFO("AnimationSystem is shutdown!");
		}
	};
	class Renderer2D : public ECS::System<Renderer2D> {
	public:
		DECLARE_RTTI
	public:
		Renderer2D() = default;
		Renderer2D(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low) : System(id, priority) {}
		~Renderer2D() = default;
		virtual void OnInit() override {
			CORE_LOG_INFO("Renderer2D init!");
		}
		virtual void OnUpdate(Time time) override {
			CORE_LOG_INFO("Renderer2D update!");
		}
		virtual void OnShutdown() override {
			CORE_LOG_INFO("Renderer2D is shutdown!");
		}

		struct TextParams
		{
			glm::vec4 Color{ 1.0f };
			float Kerning = 0.0f;
			float LineSpacing = 0.0f;
		};
		//static void DrawString(const std::string& string, Ref<Font> font, const glm::mat4& transform, const TextParams& textParams, int entityID = -1);
		//static void DrawString(const std::string& string, const glm::mat4& transform, const TextComponent& component, int entityID = -1);

		static float GetLineWidth();
		static void SetLineWidth(float width);

		// Stats
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();

	private:
		static void StartBatch();
		static void NextBatch();
	};

	class InputSystem : public ECS::System<InputSystem> {
	public:
		DECLARE_RTTI
	public:
		InputSystem() = default;
		InputSystem(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low) : System(id, priority) {}
		~InputSystem() = default;
		virtual void OnInit() override {
			CORE_LOG_INFO("InputSystem init!");
		}
		virtual void OnUpdate(Time time) override {
			CORE_LOG_INFO("InputSystem update!");
		}
		virtual void OnShutdown() override {
			CORE_LOG_INFO("InputSystem is shutdown!");
		}
	};

	class ScriptingSystem : public ECS::System<ScriptingSystem> {
	public:
		DECLARE_RTTI
	};
}