#include "pch.h"
#include "OrthographicCameraController.h"

#include "Core/Input/InputState.h"
#include "Core/Input/Keycode.h"
#include"Core/Logger/Logger.h"
namespace SerenEngine {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(float ts)
	{

        if (glm::length(m_MoveDirection) > 0.0f)
        {
            glm::vec3 normalizedDir = glm::normalize(m_MoveDirection);
            m_CameraPosition += normalizedDir * m_CameraTranslationSpeed * ts;
            CORE_LOG_TRACE("Camera pos: {0},{1},{2}",m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z);
        }
        m_Camera.SetPosition(m_CameraPosition);

        if (m_Rotation)
        {
            m_CameraRotation += m_CameraRotationSpeed * m_RotationDelta * ts;
            if (m_CameraRotation > 180.0f)
                m_CameraRotation -= 360.0f;
            else if (m_CameraRotation <= -180.0f)
                m_CameraRotation += 360.0f;
            m_Camera.SetRotation(m_CameraRotation);
        }
        m_CameraTranslationSpeed = m_ZoomLevel;
	}

    void OrthographicCameraController::OnProcessInput(const InputState& input)
    {
		//CORE_LOG_TRACE("OrthographicCameraController::OnProcessInput");
        m_MoveDirection = glm::vec3(0.0f);
        m_RotationDelta = 0.0f;

        if (input.Keyboard->IsPressed(EKeyCode::A))
            m_MoveDirection.x -= 1.0f;
        if (input.Keyboard->IsPressed(EKeyCode::D))
            m_MoveDirection.x += 1.0f;
        if (input.Keyboard->IsPressed(EKeyCode::W))
            m_MoveDirection.y += 1.0f;
        if (input.Keyboard->IsPressed(EKeyCode::S))
            m_MoveDirection.y -= 1.0f;

        if (m_Rotation)
        {
            if (input.Keyboard->IsPressed(EKeyCode::Q))
                m_RotationDelta += 1.0f;
            if (input.Keyboard->IsPressed(EKeyCode::E))
                m_RotationDelta -= 1.0f;
        }
    }


	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolledEvent(const MouseScrolledEvent& e)
	{
		//CORE_LOG_TRACE("OrthographicCameraController::OnMouseScrolledEvent");
		m_ZoomLevel -= e.GetScrollY() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResizedEvent(const WindowResizedEvent& e)
	{
		//CORE_LOG_TRACE("OrthographicCameraController::OnWindowResizedEvent");
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}