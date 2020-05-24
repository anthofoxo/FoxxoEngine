#include "foxepch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"
#include <glad/glad.h>

namespace FoxxoEngine
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int x, y, c;

		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &x, &y, &c, 0);
		FOXE_CORE_ASSERT(data, "Failed to load image");

		m_Width = x;
		m_Height = y;

		unsigned int format = GL_RGB;
		unsigned int formati = GL_RGB8;

		if (c == 3)
		{
			format = GL_RGB;
			formati = GL_RGB8;
		}
		else if (c == 4)
		{
			format = GL_RGBA;
			unsigned int formati = GL_RGBA8;
		}
		else
		{
			FOXE_CORE_ASSERT(false, "Incorrect channel count");
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_Handle);
		glTextureStorage2D(m_Handle, 1, formati, m_Width, m_Height);

		glTextureParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTextureSubImage2D(m_Handle, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_Handle);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_Handle);
	}
}