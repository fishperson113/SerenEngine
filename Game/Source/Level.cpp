#include"Level.h"
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
void Level::Init()
{
	m_TriangleTexture = Texture::Create("Assets/Textures/Triangle.png");
	m_Player.LoadAssets();
	m_PillarTarget = 150.0f;
	m_Pillars.resize(20);
	for (int i = 0; i < 20; i++)
		CreatePillar(i, i * 200.0f);
}

void Level::OnUpdate(SerenEngine::Time ts)
{
	m_Player.OnUpdate(ts);

	if (CollisionTest())
	{
		GameOver();
		return;
	}

	if (m_Player.GetPosition().x > m_PillarTarget)
	{
		CreatePillar(m_PillarIndex, m_PillarTarget + 200.0f);
		m_PillarIndex = ++m_PillarIndex % m_Pillars.size();
		m_PillarTarget += 200.0f;
	}
}

void Level::OnRender()
{
	const auto& playerPos = m_Player.GetPosition();

	glm::vec4 color = HSVtoRGB(m_PillarHSV);

	//// Floor and ceiling
	Renderer::DrawQuad({ playerPos.x,Application::Get().GetWindow()->GetHeight()/2}, {Application::Get().GetWindow()->GetWidth(), -200.0f}, color);
	Renderer::DrawQuad({ playerPos.x,-Application::Get().GetWindow()->GetHeight()/2}, {Application::Get().GetWindow()->GetWidth(), 200.0f }, color);

	for (auto& pillar : m_Pillars)
	{
		Renderer::DrawSprite(pillar.TopPosition, glm::radians(180.0f), m_TriangleTexture, pillar.TopScale, color);
		Renderer::DrawSprite(pillar.BottomPosition, 0.0f, m_TriangleTexture ,pillar.BottomScale, color);
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

	m_PillarTarget = 150.0f;
	m_PillarIndex = 0;
	for (int i = 0; i < 20; i++)
		CreatePillar(i, i * 200.0f);
}

void Level::CreatePillar(int index, float offset)
{
	Pillar& pillar = m_Pillars[index];
	pillar.TopPosition.x = offset;
	pillar.BottomPosition.x = offset;
	pillar.TopPosition.z = index * 0.1f - 0.5f;
	pillar.BottomPosition.z = index * 0.1f - 0.5f + 0.05f;

	float height = Application::Get().GetWindow()->GetHeight();
	float topBase = height * 0.5f;
	float bottomBase = -height * 0.5f;

	float base = height / 72.0f;

	float center = Random::Float() * (35.0f * base) - (17.5f * base);
	float gap = 1.0f * base + Random::Float() * (2.0f * base);

	pillar.TopPosition.y = topBase - ((topBase - center) * 0.2f) + gap * 0.5f;
	pillar.BottomPosition.y = bottomBase - ((bottomBase - center) * 0.2f) - gap * 0.5f;
}

bool Level::CollisionTest()
{
	if (glm::abs(m_Player.GetPosition().y) > (Application::Get().GetWindow()->GetHeight() / 2)-125)
		return true;
	return false;
}

void Level::GameOver()
{
	m_GameOver = true;
}
