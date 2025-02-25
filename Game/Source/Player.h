#pragma once
#include"SerenEngine.h"
#include "Random.h"
#include"box2d/box2d.h"
constexpr float PPM = 30.0f;
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
	const glm::vec2& GetPosition() const { return m_Position; }

	uint32_t GetScore() const { return (uint32_t)(m_Position.x + 10.0f) / 10.0f; }
	const SerenEngine::Texture* GetTexture() { return m_ShipTexture; }

	void Spawn(b2World* world, const b2Vec2& position, float scale, void* userData = nullptr);

	void Despawn(b2World* world);

	b2Body* Player::GetBody() { return m_Body; }
private:
	float m_Speed = 5.f;
	float m_Rotation = 0.0f;
	glm::vec2 m_Position ;

	float m_EnginePower = 200.f;


	SerenEngine::Texture* m_ShipTexture;
	SerenEngine::InputState m_InputState;

	b2Body* m_Body = nullptr;
};