#include "foxepch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace FoxxoEngine
{
	OpenGLShader::OpenGLShader(const std::string& vertSrc, const std::string& fragSrc)
		: m_Handle(0)
	{
		GLint status;
		const char* source;

		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = vertSrc.c_str();
		glShaderSource(vertShader, 1, &source, 0);
		glCompileShader(vertShader);

		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			FOXE_CORE_ERROR("{0}", infoLog.data());
			FOXE_CORE_ASSERT(false, "Vertex shader compilation failure");

			return;
		}

		source = fragSrc.c_str();
		glShaderSource(fragShader, 1, &source, 0);
		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			FOXE_CORE_ERROR("{0}", infoLog.data());
			FOXE_CORE_ASSERT(false, "Fragment shader compilation failure");

			return;
		}

		m_Handle = glCreateProgram();

		glAttachShader(m_Handle, vertShader);
		glAttachShader(m_Handle, fragShader);

		glLinkProgram(m_Handle);
		glGetProgramiv(m_Handle, GL_LINK_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_Handle, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_Handle, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_Handle);
			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			FOXE_CORE_ERROR("{0}", infoLog.data());
			FOXE_CORE_ASSERT(false, "Shader link failure");

			return;
		}

		glDetachShader(m_Handle, vertShader);
		glDetachShader(m_Handle, fragShader);

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		FOXE_CORE_ASSERT(m_Handle, "Shader deletion attemp, shader never created");
		glDeleteProgram(m_Handle);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_Handle);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniform1f(const std::string& name, float value)
	{
		int location = glGetUniformLocation(m_Handle, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniform2f(const std::string& name, const glm::vec2& value)
	{
		int location = glGetUniformLocation(m_Handle, name.c_str());
		glUniform2fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniform3f(const std::string& name, const glm::vec3& value)
	{
		int location = glGetUniformLocation(m_Handle, name.c_str());
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniform4f(const std::string& name, const glm::vec4& value)
	{
		int location = glGetUniformLocation(m_Handle, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniform1i(const std::string& name, int value)
	{
		int location = glGetUniformLocation(m_Handle, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniform2i(const std::string& name, const glm::ivec2& value)
	{
		int location = glGetUniformLocation(m_Handle, name.c_str());
		glUniform2iv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniform3i(const std::string& name, const glm::ivec3& value)
	{
		int location = glGetUniformLocation(m_Handle, name.c_str());
		glUniform3iv(location, 1, glm::value_ptr(value));
	}
	void OpenGLShader::UploadUniform4i(const std::string& name, const glm::ivec4& value)
	{
		int location = glGetUniformLocation(m_Handle, name.c_str());
		glUniform4iv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformMat2f(const std::string& name, const glm::mat2& value)
	{
		int location = glGetUniformLocation(m_Handle, name.c_str());
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformMat3f(const std::string& name, const glm::mat3& value)
	{
		int location = glGetUniformLocation(m_Handle, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformMat4f(const std::string& name, const glm::mat4& value)
	{
		int location = glGetUniformLocation(m_Handle, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}