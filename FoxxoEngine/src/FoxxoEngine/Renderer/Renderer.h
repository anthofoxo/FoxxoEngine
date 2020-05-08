#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace FoxxoEngine
{
	struct Renderer
	{
		static void BeginScene(OrthoCamera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao);

		inline static RendererApi::Api GetApi() { return RendererApi::GetApi(); }

		struct SceneData
		{
			glm::mat4 ProjectionMatrix;
			glm::mat4 ViewMatrix;
		};

		static SceneData* s_SceneData;
	};
}