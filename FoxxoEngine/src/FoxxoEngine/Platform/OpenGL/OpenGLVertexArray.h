#pragma once

#include "FoxxoEngine/Renderer/VertexArray.h"

namespace FoxxoEngine
{
	struct OpenGLVertexArray : public VertexArray
	{
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer) override;

		inline virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& buffer) override;

		uint32_t m_Handle;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}