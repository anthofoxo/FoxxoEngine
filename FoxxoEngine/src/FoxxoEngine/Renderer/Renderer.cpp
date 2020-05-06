#include "foxepch.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace FoxxoEngine
{
	namespace RendererConstants
	{
		uint32_t FOXE_ARRAY_BUFFER = GL_ARRAY_BUFFER;
		uint32_t FOXE_ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER;
		uint32_t FOXE_STATIC_DRAW = GL_STATIC_DRAW;
	}

	RendererAPI Renderer::api = RendererAPI::OpenGL;
}