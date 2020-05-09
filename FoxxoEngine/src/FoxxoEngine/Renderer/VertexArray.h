#pragma once

#include <memory>

#include "FoxxoEngine/Renderer/Buffer.h"

namespace FoxxoEngine
{
	struct VertexArray
	{
		virtual ~VertexArray() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer) = 0;

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& buffer) = 0;

		static VertexArray* Create();
	};
}
