#pragma once

#include "OrthographicCamera.h"
#include "Core/Time/Time.h"
#include "Core/Input/InputState.h"
#include "Core/Event/EventContext.h"

namespace SerenEngine {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController() {};
		OrthographicCameraController(float aspectRatio, float windowHeight, bool rotation = false);

		void OnUpdate(float ts);
		void OnProcessInput(const InputState& input);


		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
		bool OnWindowResizedEvent(const WindowResizedEvent& e);
		bool OnMouseScrolledEvent(const MouseScrolledEvent& e);
	private:
		void OnResize(float width, float height);
	private:
		float m_AspectRatio;
		float m_ZoomLevel;
		OrthographicCamera m_Camera;
		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

		glm::vec3 m_MoveDirection = { 0.0f, 0.0f, 0.0f };
		float m_RotationDelta = 0.0f;
	};

}