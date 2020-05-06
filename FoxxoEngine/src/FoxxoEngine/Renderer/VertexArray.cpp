#include "foxepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace FoxxoEngine
{
	VertexArray* VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::None: FOXE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		FOXE_CORE_ASSERT(false, "Unknown rendering api");
		return nullptr;
	}
}
