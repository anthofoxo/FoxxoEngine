#include "foxepch.h"
#include "Shader.h"
#include "FoxxoEngine/Renderer/Renderer.h"
#include "FoxxoEngine/Platform/OpenGL/OpenGLShader.h"

namespace FoxxoEngine
{
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None: FOXE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererApi::Api::OpenGL: return new OpenGLShader(filepath);
		}

		FOXE_CORE_ASSERT(false, "Unknown rendering api");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertSrc, const std::string& fragSrc)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None: FOXE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererApi::Api::OpenGL: return new OpenGLShader(vertSrc, fragSrc);
		}

		FOXE_CORE_ASSERT(false, "Unknown rendering api");
		return nullptr;
	}
}