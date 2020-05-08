#pragma once

#include "FoxxoEngine/Renderer/Shader.h"

namespace FoxxoEngine
{
	struct OpenGLShader : public Shader
	{
		OpenGLShader(const std::string& vertSrc, const std::string& fragSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4f(const std::string& name, const glm::mat4& matrix) override;

		uint32_t m_Handle;
	};
}