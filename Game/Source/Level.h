#pragma once

#include "Player.h"
#include"box2d/box2d.h"
#include"box2d/box2d.h"
using namespace SerenEngine;
struct Pillar
{
	glm::vec3 TopPosition = { 0.0f, Application::Get().GetWindow()->GetHeight()/2, 0.0f};
	float TopScale = 0.5f;

	glm::vec3 BottomPosition = { 50.0f, -Application::Get().GetWindow()->GetHeight() / 2, 0.0f };
	float BottomScale = 0.5f;
};

class Level
{
public:
	void Init();
	void Init(b2World* world);
	void OnUpdate(SerenEngine::Time ts);
	void OnRender();

	void OnImGuiRender();

	bool IsGameOver() const { return m_GameOver; }
	void Reset();

	Player& GetPlayer() { return m_Player; }

	
private:
	void RepositioningPillar(Pillar& pillar, float offset);
	bool CollisionTest();

	void GameOver();
private:
	Player m_Player;

	bool m_GameOver = false;

	float m_PillarTarget = 150.0f;
	int m_PillarIndex = 0;
	glm::vec3 m_PillarHSV = { 0.0f, 0.8f, 0.8f };

	std::vector<Pillar> m_Pillars;

	SerenEngine::Texture* m_TriangleTexture;
};