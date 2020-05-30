#include "foxepch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace FoxxoEngine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(void* data, size_t size)
	{
		FOXE_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_Handle);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		FOXE_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_Handle);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		FOXE_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		FOXE_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(void* data, size_t size)
	{
		FOXE_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_Handle);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		m_Count = (unsigned int) size / sizeof(unsigned int);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		FOXE_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_Handle);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		FOXE_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		FOXE_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}