#pragma once

#include "FoxxoEngine/Renderer/Buffer.h"

namespace FoxxoEngine
{
	struct OpenGLVertexBuffer : public VertexBuffer
	{
		OpenGLVertexBuffer(void* data, size_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		uint32_t m_Handle;
		BufferLayout m_Layout;
	};

	struct OpenGLIndexBuffer : public IndexBuffer
	{
		OpenGLIndexBuffer(void* data, size_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual int GetCount() const override { return m_Count; }

		uint32_t m_Handle;
		BufferLayout m_Layout;
		int m_Count;
	};
}