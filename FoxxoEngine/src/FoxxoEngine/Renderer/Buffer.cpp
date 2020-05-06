#include "foxepch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace FoxxoEngine
{

	Buffer* Buffer::create(uint32_t type, uint32_t drawMode, void *data, size_t size)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::None: FOXE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLBuffer(type, drawMode, data, size);
		}

		FOXE_CORE_ASSERT(false, "Unknown rendering api");
		return nullptr;
	}
}