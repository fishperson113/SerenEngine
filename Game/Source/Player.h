#pragma once
#include"SerenEngine.h"
#include "Random.h"
class Player
{
public:
	Player();

	void LoadAssets();

	void OnUpdate(SerenEngine::Time ts);
	void OnRender();

	void OnImGuiRender();

	void Reset();

	void SetInputState(const SerenEngine::InputState& input) { m_InputState = input; }
	float GetRotation() {
		float rotation = m_Velocity.y * 4.0f - 90.0f;
		return glm::clamp(rotation, -90.0f, 90.0f);
	}
	const glm::vec2& GetPosition() const { return m_Position; }

	uint32_t GetScore() const { return (uint32_t)(m_Position.x + 10.0f) / 10.0f; }
	const SerenEngine::Texture* GetTexture() { return m_ShipTexture; }
private:
	float m_Speed = 50.f;
	glm::vec2 m_Position = { -10.0f, 0.0f };
	glm::vec2 m_Velocity = { 5.0f, 0.0f };

	float m_EnginePower = 100.f;
	float m_Gravity = 100.f;

	float m_Time = 0.0f;

	SerenEngine::Texture* m_ShipTexture;
	SerenEngine::InputState m_InputState;
};