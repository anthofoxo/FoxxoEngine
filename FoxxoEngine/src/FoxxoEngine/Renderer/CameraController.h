#pragma once

#include "FoxxoEngine/Renderer/Camera.h"

#include "FoxxoEngine/Event/ApplicationEvent.h"
#include "FoxxoEngine/Event/MouseEvent.h"

namespace FoxxoEngine
{
	class OrthoCameraController
	{
	public:
		OrthoCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate();
		void OnEvent(Event& e);

		inline OrthoCamera& GetCamera() { return m_Camera; }
		inline const OrthoCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseSrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthoCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 1.0f;
		float m_CameraRotationSpeed = 90.0f;
	};
}