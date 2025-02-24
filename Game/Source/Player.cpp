#include"Player.h"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace SerenEngine;
Player::Player()
{
}

void Player::LoadAssets()
{
	m_ShipTexture = Texture::Create("Assets/Textures/Ship.png");
}

void Player::OnUpdate(SerenEngine::Time ts)
{
	m_Time += ts.GetDeltaTime();
	if (m_InputState.Keyboard->GetValue(EKeyCode::SPACE)) {
		m_Velocity.y += m_EnginePower;
		if (m_Velocity.y < 0.0f)
			m_Velocity.y += m_EnginePower * 2.0f;
	}
	else {
		m_Velocity.y -= m_Gravity;
	}
	m_Velocity.x = m_Speed;
	m_Position += m_Velocity * ts.GetDeltaTime();
}

void Player::OnRender()
{
	Renderer::DrawSprite({ m_Position.x, m_Position.y, 0.5f }, glm::radians(GetRotation()), m_ShipTexture, 5.f, glm::vec4(1.0f));
}

void Player::OnImGuiRender()
{
	ImGui::DragFloat("Engine Power", &m_EnginePower, 0.1f);
	ImGui::DragFloat("Gravity", &m_Gravity, 0.1f);
	ImGui::DragFloat("Speed", &m_Speed, 0.1f);
}

void Player::Reset()
{
	m_Position = { -10.0f, 0.0f };
	m_Velocity = { 5.0f, 0.0f };
}
