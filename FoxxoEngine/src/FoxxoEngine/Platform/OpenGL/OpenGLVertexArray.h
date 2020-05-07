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

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;

		inline virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override;

		uint32_t m_Handle;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}