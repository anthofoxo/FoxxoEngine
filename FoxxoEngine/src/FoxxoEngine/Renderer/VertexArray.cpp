#include "foxepch.h"
#include "VertexArray.h"

#include "FoxxoEngine/Renderer/Renderer.h"
#include "FoxxoEngine/Platform/OpenGL/OpenGLVertexArray.h"

namespace FoxxoEngine
{
	VertexArray* VertexArray::create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: FOXE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		FOXE_CORE_ASSERT(false, "Unknown rendering api");
		return nullptr;
	}
}
