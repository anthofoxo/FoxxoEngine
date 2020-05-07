#pragma once

#include "RenderCommand.h"

namespace FoxxoEngine
{
	struct Renderer
	{
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vao);

		inline static RendererApi::Api GetApi() { return RendererApi::GetApi(); }
	};
}