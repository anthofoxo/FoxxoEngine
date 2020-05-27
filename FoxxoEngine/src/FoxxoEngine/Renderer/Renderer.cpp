#include "foxepch.h"
#include "Renderer.h"

#include "FoxxoEngine/Platform/OpenGL/OpenGLShader.h"

namespace FoxxoEngine
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthoCamera& camera)
	{
		s_SceneData->ProjectionMatrix = camera.GetProjectionMatrix();
		s_SceneData->ViewMatrix = camera.GetViewMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vao, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4f("u_Projection", s_SceneData->ProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4f("u_View", s_SceneData->ViewMatrix);

		vao->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4f("u_Model", transform);
		RenderCommand::DrawIndexed(vao);
	}
}