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

		virtual void AddVertexBuffer(const std::shared_ptr<Buffer>& buffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<Buffer>& buffer) = 0;

		static VertexArray* create();
	};
}
