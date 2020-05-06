#include "foxepch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace FoxxoEngine
{
	OpenGLBuffer::OpenGLBuffer(uint32_t type, uint32_t drawMode, void* data, size_t size)
	{
		m_Type = type;

		glCreateBuffers(1, &m_Handle);
		Bind();
		glBufferData(m_Type, size, data, drawMode);
	}

	OpenGLBuffer::~OpenGLBuffer()
	{
		glDeleteBuffers(1, &m_Handle);
	}

	void OpenGLBuffer::Bind() const
	{
		glBindBuffer(m_Type, m_Handle);
	}

	void OpenGLBuffer::Unbind() const
	{
		glBindBuffer(m_Type, 0);
	}
}