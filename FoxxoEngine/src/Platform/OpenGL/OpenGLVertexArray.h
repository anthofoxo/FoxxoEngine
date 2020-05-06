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

		virtual void AddVertexBuffer(const std::shared_ptr<Buffer> &buffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<Buffer> &buffer) override;

		uint32_t m_handle;
		std::vector<std::shared_ptr<Buffer>> m_vertexBuffers;
		std::shared_ptr<Buffer> m_indexBuffer;
	};
}