#pragma once

#include "VertexArray.h"
#include <glm/glm.hpp>

namespace FoxxoEngine
{
	struct RendererApi
	{
		enum struct Api
		{
			None, OpenGL
		};

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vao) = 0;

		inline static Api GetApi() { return s_Api; }

	private:
		static Api s_Api;
	};
}