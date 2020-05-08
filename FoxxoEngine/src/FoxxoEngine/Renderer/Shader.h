#pragma once

#include <string>

#include <glm/glm.hpp>

namespace FoxxoEngine
{
	struct Shader
	{
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4f(const std::string& name, const glm::mat4& matrix) = 0;

		static Shader* Create(const std::string& vertSrc, const std::string& fragSrc);
	};
}