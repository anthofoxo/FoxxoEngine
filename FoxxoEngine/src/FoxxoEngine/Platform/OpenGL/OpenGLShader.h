#pragma once

#include "FoxxoEngine/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace FoxxoEngine
{
	struct OpenGLShader : public Shader
	{
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertSrc, const std::string& fragSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniform1f(const std::string& name, float value);
		void UploadUniform2f(const std::string& name, const glm::vec2& value);
		void UploadUniform3f(const std::string& name, const glm::vec3& value);
		void UploadUniform4f(const std::string& name, const glm::vec4& value);

		void UploadUniform1i(const std::string& name, int value);
		void UploadUniform2i(const std::string& name, const glm::ivec2& value);
		void UploadUniform3i(const std::string& name, const glm::ivec3& value);
		void UploadUniform4i(const std::string& name, const glm::ivec4& value);

		void UploadUniformMat2f(const std::string& name, const glm::mat2& value);
		void UploadUniformMat3f(const std::string& name, const glm::mat3& value);
		void UploadUniformMat4f(const std::string& name, const glm::mat4& value);

		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
		void Compile(const std::unordered_map<GLenum, std::string>& srcs);

		uint32_t m_Handle;
	};
}