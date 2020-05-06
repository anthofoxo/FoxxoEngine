#pragma once

#include <string>

namespace FoxxoEngine
{
	class Shader
	{
	public:
		Shader(const std::string &vertSrc, const std::string &FragSrc);
		~Shader();

		void bind() const;
		void unbind() const;

		uint32_t m_handle = 0;
	private:
		
	};
}