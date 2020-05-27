#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace FoxxoEngine
{
	struct Renderer
	{
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthoCamera& camera);
		static void EndScene();
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vao, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererApi::Api GetApi() { return RendererApi::GetApi(); }

		struct SceneData
		{
			glm::mat4 ProjectionMatrix;
			glm::mat4 ViewMatrix;
		};

		static SceneData* s_SceneData;
	};
}