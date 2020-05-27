#include "foxepch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>

namespace FoxxoEngine
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vert") return GL_VERTEX_SHADER;
		if (type == "tesc") return GL_TESS_CONTROL_SHADER;
		if (type == "tese") return GL_TESS_EVALUATION_SHADER;
		if (type == "geom") return GL_GEOMETRY_SHADER;
		if (type == "frag") return GL_FRAGMENT_SHADER;

		FOXE_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_Handle(0)
	{
		std::string src = ReadFile(filepath);
		auto srcs = PreProcess(src);
		Compile(srcs);
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& src)
	{
		std::unordered_map<GLenum, std::string>  srcs;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = src.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t eol = src.find_first_of("\r\n", pos);
			FOXE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = src.substr(begin, eol - begin);
			FOXE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = src.find_first_not_of("\r\n", eol);
			pos = src.find(typeToken, nextLinePos);
			srcs[ShaderTypeFromString(type)] = src.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? src.size() - 1 : nextLinePos));
		}

		return srcs;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& srcs)
	{
		GLint status;
		GLuint program = glCreateProgram();

		// std::vector<GLenum> shaders;
		// shaders.reserve(srcs.size());

		constexpr int maxShaders = 2;

		FOXE_CORE_ASSERT(srcs.size() <= maxShaders, "Max shader limit {0}, {1} given", maxShaders, srcs.size());

		std::array<GLenum, maxShaders> shaders;
		int shaderIndex = 0;

		for (auto&& [type, src] : srcs)
		{
			GLuint shader = glCreateShader(type);

			const GLchar* srcC = src.c_str();
			glShaderSource(shader, 1, &srcC, 0);

			glCompileShader(shader);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

			if (status == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				FOXE_CORE_ERROR("{0}", infoLog.data());
				FOXE_CORE_ASSERT(false, "Shader compilation failure");

				break;
			}

			glAttachShader(program, shader);
			// shaders.push_back(shader);
			shaders[shaderIndex++] = shader;
		}

		m_Handle = program;

		glLinkProgram(m_Handle);
		glGetProgramiv(m_Handle, GL_LINK_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_Handle, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_Handle, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_Handle);

			for (auto shader : shaders)
				glDeleteShader(shader);

			FOXE_CORE_ERROR("{0}", infoLog.data());
			FOXE_CORE_ASSERT(false, "Shader link failure");

			return;
		}

		for (auto shader : shaders)
		{
			glDetachShader(m_Handle, shader);
			glDeleteShader(shader);
		}
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;

		std::ifstream in(filepath, std::ios::in | std::ios::binary);

		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			FOXE_CORE_ERROR("Failed to open file {0}", filepath);
		}

		return result;
	}

	OpenGLShader::OpenGLShader(const std::string& vertSrc, const std::string& fragSrc)
	{
		std::unordered_map<GLenum, std::string> map;
		map[GL_VERTEX_SHADER] = vertSrc;
		map[GL_FRAGMENT_SHADER] = fragSrc;
		Compile(map);
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