#pragma once

#include "FoxxoEngine/Renderer/Texture.h"

namespace FoxxoEngine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(unsigned int width, unsigned int height, unsigned char* data);
		virtual ~OpenGLTexture2D();

		inline virtual uint32_t GetWidth() const override { return m_Width; }
		inline virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot) const override;
	private:

		std::string m_Path;
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_Handle;
	};
}