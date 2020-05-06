#include "foxepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace FoxxoEngine
{
	static GLenum ShaderDataTypeGLType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat2:		return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}

		FOXE_CORE_ASSERT(false, "Unknown shader datatype");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_Handle);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_Handle);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_Handle);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<Buffer>& buffer)
	{
		FOXE_CORE_ASSERT(buffer->GetLayout().m_Elements.size(), "Vertex buffer, no layout specified");

		Bind();
		buffer->Bind();

		uint32_t index = 0;
		const BufferLayout &layout = buffer->GetLayout();
		for (const auto &element : layout)
		{
			glVertexAttribPointer(index, ShaderDataTypeCount(element.m_Type), ShaderDataTypeGLType(element.m_Type), element.m_Normalized ? GL_TRUE : GL_FALSE, layout.m_Stride, (const void*) element.m_Offset);
			glEnableVertexAttribArray(index);

			++index;
		}

		m_VertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<Buffer>& buffer)
	{
		glBindVertexArray(m_Handle);
		buffer->Bind();

		m_IndexBuffer = buffer;
	}
}