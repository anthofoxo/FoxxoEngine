#include "foxepch.h"
#include "OpenGLRendererApi.h"

#include <glad/glad.h>

namespace FoxxoEngine
{
	void OpenGLRendererApi::Init()
	{
		FOXE_PROFILE_FUNCTION();

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererApi::SetClearColor(const glm::vec4& color)
	{
		FOXE_PROFILE_FUNCTION();

		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererApi::Clear()
	{
		FOXE_PROFILE_FUNCTION();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererApi::DrawIndexed(const Ref<VertexArray>& vao)
	{
		FOXE_PROFILE_FUNCTION();

		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererApi::SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
	{
		FOXE_PROFILE_FUNCTION();

		glViewport(x, y, w, h);
	}
}