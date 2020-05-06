#include "foxepch.h"
#include "Buffer.h"

#include "FoxxoEngine/Renderer/Renderer.h"
#include "FoxxoEngine/Platform/OpenGL/OpenGLBuffer.h"

namespace FoxxoEngine
{
	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
	: m_Elements(elements)
	{
		uint32_t offset = 0;
		m_Stride = 0;

		for (auto& element : m_Elements)
		{
			element.m_Offset = offset;
			offset += element.m_Size;
			m_Stride += element.m_Size;
		}
	}

	Buffer* Buffer::Create(uint32_t type, uint32_t drawMode, void* data, size_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: FOXE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLBuffer(type, drawMode, data, size);
		}

		FOXE_CORE_ASSERT(false, "Unknown rendering api");
		return nullptr;
	}
}