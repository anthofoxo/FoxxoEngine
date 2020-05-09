#pragma once

#include <glm/glm.hpp>

namespace FoxxoEngine
{
	class OrthoCamera
	{
	public:
		OrthoCamera(float left, float right, float bottom, float top);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; Recalc(); }

		inline float GetRotation() const { return m_Rotation; }
		inline void SetRotation(float rotation) { m_Rotation = rotation; Recalc(); }

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

	private:
		void Recalc();
	private:
		glm::vec3 m_Position;
		float m_Rotation = 0.0f;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
	};
}