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
    if (m_Body)
    {
        bool flapping = m_InputState.Keyboard->GetValue(EKeyCode::SPACE);
        if (flapping)
        {
            b2Vec2 impulse(0.0f, m_EnginePower);
            m_Body->ApplyLinearImpulse(impulse, m_Body->GetWorldCenter(), true);
        }

        b2Vec2 velocity = m_Body->GetLinearVelocity();
        velocity.x = m_Speed; 
        m_Body->SetLinearVelocity(velocity);
        float targetAngle;
        if (flapping)
        {
            targetAngle = glm::radians(40.0f);
        }
        else
        {
            targetAngle = glm::radians(-40.0f);
        }

        // Nội suy góc hiện tại về góc mục tiêu
        float currentAngle = m_Body->GetAngle();
        float lerpFactor = 5.0f * ts.GetDeltaTime(); // điều chỉnh tốc độ xoay
        float newAngle = currentAngle + (targetAngle - currentAngle) * lerpFactor;

        m_Body->SetTransform(m_Body->GetPosition(), newAngle);

        b2Vec2 physPos = m_Body->GetPosition();
        m_Position = glm::vec2(physPos.x, physPos.y);
        m_Rotation = m_Body->GetAngle();
    }
}

void Player::OnRender()
{
    glm::vec2 pixelPos = m_Position * PPM;

    Renderer::DrawSprite({ pixelPos.x, pixelPos.y, 0.5f }, m_Rotation-glm::radians(90.0f), m_ShipTexture, 5.f, glm::vec4(1.0f));
}

void Player::OnImGuiRender()
{
	ImGui::DragFloat("Engine Power", &m_EnginePower, 0.1f);
	ImGui::DragFloat("Speed", &m_Speed, 0.1f);
}

void Player::Reset()
{
	m_Position = { -10.0f, 0.0f };

    if (m_Body)
    {
        m_Body->SetTransform(b2Vec2(-10.0f, 0.0f), 0.0f);
        m_Body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        m_Body->SetAngularVelocity(0.0f);
    }
}

void Player::Spawn(b2World* world, const b2Vec2& position, float scale, void* userData)
{
    if (m_Body != nullptr)
        return;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(position.x / PPM, position.y / PPM);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(userData);

    m_Body = world->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(scale * 0.5f, scale * 0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 5.0f;
    fixtureDef.friction = 0.3f;

    m_Body->CreateFixture(&fixtureDef);
}

void Player::Despawn(b2World* world)
{
    if (m_Body)
    {
        world->DestroyBody(m_Body);
        m_Body = nullptr;
    }
}
