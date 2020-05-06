#include "foxepch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace FoxxoEngine
{
	OpenGLBuffer::OpenGLBuffer(uint32_t type, uint32_t drawMode, void *data, size_t size)
	{
		m_type = type;

		glCreateBuffers(1, &m_handle);
		bind();
		glBufferData(m_type, size, data, drawMode);
	}

	OpenGLBuffer::~OpenGLBuffer()
	{
		glDeleteBuffers(1, &m_handle);
	}

	void OpenGLBuffer::bind() const
	{
		glBindBuffer(m_type, m_handle);
	}

	void OpenGLBuffer::unbind() const
	{
		glBindBuffer(m_type, 0);
	}

}