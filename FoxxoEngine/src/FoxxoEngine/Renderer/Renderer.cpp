#include "foxepch.h"
#include "Renderer.h"

namespace FoxxoEngine
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vao)
	{
		vao->Bind();
		RenderCommand::DrawIndexed(vao);
	}
}