#pragma once

#include "FoxxoEngine/Renderer/Buffer.h"

namespace FoxxoEngine
{
	struct OpenGLBuffer : public Buffer
	{
		OpenGLBuffer(uint32_t type, uint32_t drawMode, void* data, size_t size);
		virtual ~OpenGLBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		uint32_t m_Handle;
		uint32_t m_Type;
		BufferLayout m_Layout;
	};
}