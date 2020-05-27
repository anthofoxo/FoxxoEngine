#include "foxepch.h"
#include "CameraController.h"

#include "FoxxoEngine/Application.h"
#include "FoxxoEngine/Input.h"
#include "FoxxoEngine/InputCodes.h"

namespace FoxxoEngine
{
	OrthoCameraController::OrthoCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthoCameraController::OnUpdate()
	{
		float deltatime = (float) Application::Get().GetDeltaTime();

		float speed = m_CameraTranslationSpeed * deltatime * m_ZoomLevel;

		if (Input::IsKeyPressed(FOXE_KEY_A) | Input::IsKeyPressed(FOXE_KEY_LEFT))
			m_CameraPosition.x -= speed;

		if (Input::IsKeyPressed(FOXE_KEY_D) | Input::IsKeyPressed(FOXE_KEY_RIGHT))
			m_CameraPosition.x += speed;

		if (Input::IsKeyPressed(FOXE_KEY_S) | Input::IsKeyPressed(FOXE_KEY_DOWN))
			m_CameraPosition.y -= speed;

		if (Input::IsKeyPressed(FOXE_KEY_W) | Input::IsKeyPressed(FOXE_KEY_UP))
			m_CameraPosition.y += speed;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(FOXE_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * deltatime;

			if (Input::IsKeyPressed(FOXE_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * deltatime;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(FOXE_BIND_EVENT_FN(OrthoCameraController::OnMouseSrolled));
		dispatcher.Dispatch<WindowResizeEvent>(FOXE_BIND_EVENT_FN(OrthoCameraController::OnWindowResized));
	}

	bool OrthoCameraController::OnMouseSrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.getYOffset() * 0.1f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.1f);

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthoCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}