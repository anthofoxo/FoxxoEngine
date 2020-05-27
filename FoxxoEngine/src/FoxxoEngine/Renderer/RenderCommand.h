#pragma once

#include "RendererAPI.h"

namespace FoxxoEngine
{
	struct RenderCommand
	{
		inline static void Init() { s_RendererApi->Init(); }

		inline static void SetClearColor(const glm::vec4& color) { s_RendererApi->SetClearColor(color); }
		inline static void Clear() { s_RendererApi->Clear(); }

		inline static void DrawIndexed(const Ref<VertexArray>& vao) { s_RendererApi->DrawIndexed(vao); }

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) { s_RendererApi->SetViewport(x, y, w, h); };
	private:
		static RendererApi* s_RendererApi;
	};
}