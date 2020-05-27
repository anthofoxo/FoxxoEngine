#pragma once

#include "FoxxoEngine/Renderer/RendererAPI.h"

namespace FoxxoEngine
{
	struct OpenGLRendererApi : public RendererApi
	{
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vao) override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;
	};
}