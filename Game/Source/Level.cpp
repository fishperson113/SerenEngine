#include"Level.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace SerenEngine;

static glm::vec4 HSVtoRGB(const glm::vec3& hsv) {
	int H = (int)(hsv.x * 360.0f);
	double S = hsv.y;
	double V = hsv.z;

	double C = S * V;
	double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if (H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;
	}
	else if (H >= 60 && H < 120) {
		Rs = X;
		Gs = C;
		Bs = 0;
	}
	else if (H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;
	}
	else if (H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;
	}
	else if (H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;
	}

	return { (Rs + m), (Gs + m), (Bs + m), 1.0f };
}
static bool PointInTri(const glm::vec2& p, glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2)
{
	float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
	float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

	if ((s < 0) != (t < 0))
		return false;

	float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

	return A < 0 ?
		(s <= 0 && s + t >= A) :
		(s >= 0 && s + t <= A);
}
static const std::vector<std::array<glm::vec4, 3>> localPillarCollision = {
	{ 
		glm::vec4(0.0f, 0.577f, 0.0f, 1.0f),  
		glm::vec4(-0.5f, -0.289f, 0.0f, 1.0f),
		glm::vec4(0.5f, -0.289f, 0.0f, 1.0f)  
	},
	{ 
		glm::vec4(0.0f, 0.577f, 0.0f, 1.0f),
		glm::vec4(0.5f, -0.289f, 0.0f, 1.0f),
		glm::vec4(-0.5f, -0.289f, 0.0f, 1.0f)
	}
};
void Level::Init()
{
	m_TriangleTexture = Texture::Create("Assets/Textures/Triangle.png");
	m_Player.LoadAssets();
	m_PillarTarget = 200.0f;
	m_Pillars.resize(10);
	Reset();
}
void Level::Init(b2World* worldId)
{
	m_TriangleTexture = Texture::Create("Assets/Textures/Triangle.png");
	m_Player.LoadAssets();
	b2Vec2 initialPos = { -20.0f, 0.0f };
	float playerScale = 5.0f;

	m_Player.Spawn(worldId, initialPos, playerScale, nullptr);

	m_PillarTarget = 200.0f;
	m_Pillars.resize(10);

	CreatePillarBodies(worldId);

	Reset();
}

void Level::OnUpdate(SerenEngine::Time ts)
{
	m_Player.OnUpdate(ts);

	if (CollisionTest())
	{
		GameOver();
		return;
	}

	float screenWidth = Application::Get().GetWindow()->GetWidth();
	float buffer = 50.0f; // Small buffer for smoother repositioning

	float farthestPillarX = 0.0f;
	for (const auto& pillar : m_Pillars)
	{
		farthestPillarX = std::max(farthestPillarX, pillar.TopPosition.x);
	}
	glm::vec2 playerPixelPos = m_Player.GetPosition() * PPM;
	for (auto& pillar : m_Pillars)
	{
		if (pillar.TopPosition.x < playerPixelPos.x - screenWidth / 2 - buffer)
		{
			RepositioningPillar(pillar, farthestPillarX + 200.0f);
			farthestPillarX = pillar.TopPosition.x;
		}
	}
}

void Level::OnRender()
{
	const auto& playerPos = m_Player.GetPosition();

	glm::vec4 color = HSVtoRGB(m_PillarHSV);

	for (auto& pillar : m_Pillars)
	{
		Renderer::DrawSprite(pillar.TopPosition, glm::radians(180.0f), m_TriangleTexture, pillar.TopScale, color);
		Renderer::DrawSprite(pillar.BottomPosition, 0.0f, m_TriangleTexture, pillar.BottomScale, color);
	}

	m_Player.OnRender();
}

void Level::OnImGuiRender()
{
	m_Player.OnImGuiRender();
}

void Level::Reset()
{
	m_GameOver = false;
	m_Player.Reset();

	float startOffset = (m_Player.GetPosition().x * PPM) + 200.0f;
	for (int i = 0; i < m_Pillars.size(); i++)
	{
		RepositioningPillar(m_Pillars[i], startOffset + i * 200.0f);
	}
}

void Level::RepositioningPillar(Pillar& pillar, float offset)
{
	float height = Application::Get().GetWindow()->GetHeight();
	float base = height / 72.0f;

	float center = Random::Float() * (100.0f * base) - (50.0f * base);
	float gap = 50.0f;

	pillar.TopPosition = { offset, height / 2 - ((height / 2 - center) * 0.2f) + gap * 0.5f, 0.0f };
	pillar.BottomPosition = { offset, -height / 2 - ((-height / 2 - center) * 0.2f) - gap * 0.5f, 0.0f };

	if (pillar.TopBody)
		pillar.TopBody->SetTransform(b2Vec2(pillar.TopPosition.x / PPM, pillar.TopPosition.y / PPM), 0.0f);
	if (pillar.BottomBody)
		pillar.BottomBody->SetTransform(b2Vec2(pillar.BottomPosition.x / PPM, pillar.BottomPosition.y / PPM), 0.0f);
}

bool Level::CollisionTest()
{
	glm::vec2 playerPixelPos = m_Player.GetPosition() * PPM;
	float halfScreenHeight = Application::Get().GetWindow()->GetHeight() / 2.0f;

	if (glm::abs(playerPixelPos.y) > halfScreenHeight)
		return true;

	b2Body* playerBody = m_Player.GetBody();
	if (playerBody)
	{
		for (b2Fixture* pf = playerBody->GetFixtureList(); pf; pf = pf->GetNext())
		{
			// Lặp qua từng pillar
			for (const auto& pillar : m_Pillars)
			{
				// Kiểm tra Top Pillar
				if (pillar.TopBody)
				{
					for (b2Fixture* pillarF = pillar.TopBody->GetFixtureList(); pillarF; pillarF = pillarF->GetNext())
					{
						if (b2TestOverlap(pf->GetShape(), 0,
							pillarF->GetShape(), 0,
							playerBody->GetTransform(),
							pillar.TopBody->GetTransform()))
						{
							return true;
						}
					}
				}
				// Kiểm tra Bottom Pillar
				if (pillar.BottomBody)
				{
					for (b2Fixture* pillarF = pillar.BottomBody->GetFixtureList(); pillarF; pillarF = pillarF->GetNext())
					{
						if (b2TestOverlap(pf->GetShape(), 0,
							pillarF->GetShape(), 0,
							playerBody->GetTransform(),
							pillar.BottomBody->GetTransform()))
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void Level::CreatePillarBodies(b2World* world)
{
	for (auto& pillar : m_Pillars)
	{
		b2BodyDef topBodyDef;
		topBodyDef.type = b2_staticBody;
		topBodyDef.position = b2Vec2(pillar.TopPosition.x / PPM, pillar.TopPosition.y / PPM);
		pillar.TopBody = world->CreateBody(&topBodyDef);

		b2PolygonShape topShape;
		b2Vec2 vertices[3];
		for (int i = 0; i < 3; i++)
		{
			vertices[i].Set(localPillarCollision[0][i].x * pillar.TopScale,
				localPillarCollision[0][i].y * pillar.TopScale);
		}
		topShape.Set(vertices, 3);

		b2FixtureDef topFixtureDef;
		topFixtureDef.shape = &topShape;
		topFixtureDef.density = 0.0f; 
		pillar.TopBody->CreateFixture(&topFixtureDef);

		b2BodyDef bottomBodyDef;
		bottomBodyDef.type = b2_staticBody;
		bottomBodyDef.position = b2Vec2(pillar.BottomPosition.x / PPM, pillar.BottomPosition.y / PPM);
		pillar.BottomBody = world->CreateBody(&bottomBodyDef);

		b2PolygonShape bottomShape;
		b2Vec2 vertices2[3];
		for (int i = 0; i < 3; i++)
		{
			vertices2[i].Set(localPillarCollision[1][i].x * pillar.BottomScale,
				localPillarCollision[1][i].y * pillar.BottomScale);
		}
		bottomShape.Set(vertices2, 3);

		b2FixtureDef bottomFixtureDef;
		bottomFixtureDef.shape = &bottomShape;
		bottomFixtureDef.density = 0.0f;
		pillar.BottomBody->CreateFixture(&bottomFixtureDef);
	}
}

void Level::GameOver()
{
	m_GameOver = true;
}