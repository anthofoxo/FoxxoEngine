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

		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vao) = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;

		inline static Api GetApi() { return s_Api; }

	private:
		static Api s_Api;
	};
}