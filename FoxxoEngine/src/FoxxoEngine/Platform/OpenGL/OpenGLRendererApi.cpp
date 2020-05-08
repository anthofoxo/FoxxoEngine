#include "foxepch.h"
#include "OpenGLRendererApi.h"

#include <glad/glad.h>

namespace FoxxoEngine
{
	void OpenGLRendererApi::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererApi::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererApi::DrawIndexed(const std::shared_ptr<VertexArray>& vao)
	{
		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}