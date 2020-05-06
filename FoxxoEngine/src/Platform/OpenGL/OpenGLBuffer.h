#pragma once

#include "FoxxoEngine/Renderer/Buffer.h"

namespace FoxxoEngine
{
	struct OpenGLBuffer : public Buffer
	{
		OpenGLBuffer(uint32_t type, uint32_t drawMode, void *data, size_t size);
		virtual ~OpenGLBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout &GetLayout() const override { return m_layout; }
		virtual void SetLayout(const BufferLayout &layout) override { m_layout = layout; }

		uint32_t m_handle;
		uint32_t m_type;
		BufferLayout m_layout;
	};
}