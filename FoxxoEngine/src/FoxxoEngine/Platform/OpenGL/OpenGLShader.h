#pragma once

#include "FoxxoEngine/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace FoxxoEngine
{
	struct OpenGLShader : public Shader
	{
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual const std::string& GetName() const override { return m_Name; }

		virtual void UploadUniform1f(const std::string& name, float value) override;
		virtual void UploadUniform2f(const std::string& name, const glm::vec2& value) override;
		virtual void UploadUniform3f(const std::string& name, const glm::vec3& value) override;
		virtual void UploadUniform4f(const std::string& name, const glm::vec4& value) override;

		virtual void UploadUniform1i(const std::string& name, int value) override;
		virtual void UploadUniform2i(const std::string& name, const glm::ivec2& value) override;
		virtual void UploadUniform3i(const std::string& name, const glm::ivec3& value) override;
		virtual void UploadUniform4i(const std::string& name, const glm::ivec4& value) override;

		virtual void UploadUniformMat2f(const std::string& name, const glm::mat2& value) override;
		virtual void UploadUniformMat3f(const std::string& name, const glm::mat3& value) override;
		virtual void UploadUniformMat4f(const std::string& name, const glm::mat4& value) override;

		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
		void Compile(const std::unordered_map<GLenum, std::string>& srcs);

		uint32_t m_Handle;

		std::string m_Name;
	};
}