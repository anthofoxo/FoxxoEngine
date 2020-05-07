#pragma once

#include "FoxxoEngine/Renderer/RendererAPI.h"

namespace FoxxoEngine
{
	struct OpenGLRendererApi : public RendererApi
	{
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vao) override;
	};
}