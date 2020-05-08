#include "foxepch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FoxxoEngine
{
	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
		m_Position = glm::vec3();
		m_Rotation = 0.0f;
		Recalc();
	}

	void OrthoCamera::Recalc()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
	}
}