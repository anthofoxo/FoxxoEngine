#include "foxepch.h"
#include "VertexArray.h"

#include "FoxxoEngine/Renderer/Renderer.h"
#include "FoxxoEngine/Platform/OpenGL/OpenGLVertexArray.h"

namespace FoxxoEngine
{
	VertexArray* VertexArray::create()
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None: FOXE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererApi::Api::OpenGL: return new OpenGLVertexArray();
		}

		FOXE_CORE_ASSERT(false, "Unknown rendering api");
		return nullptr;
	}
}
