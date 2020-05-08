#include "foxepch.h"
#include "Renderer.h"

namespace FoxxoEngine
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthoCamera& camera)
	{
		s_SceneData->ProjectionMatrix = camera.GetProjectionMatrix();
		s_SceneData->ViewMatrix = camera.GetViewMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao)
	{
		shader->Bind();
		shader->UploadUniformMat4f("u_Projection", s_SceneData->ProjectionMatrix);
		shader->UploadUniformMat4f("u_View", s_SceneData->ViewMatrix);

		vao->Bind();
		RenderCommand::DrawIndexed(vao);
	}
}