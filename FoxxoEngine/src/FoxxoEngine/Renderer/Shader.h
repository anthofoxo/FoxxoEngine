#pragma once

#include <string>

namespace FoxxoEngine
{
	struct Shader
	{
		Shader(const std::string& vertSrc, const std::string& fragSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		uint32_t m_Handle = 0;
	};
}