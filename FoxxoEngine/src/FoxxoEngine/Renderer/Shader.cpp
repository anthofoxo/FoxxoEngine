#include "foxepch.h"
#include "Shader.h"
#include "FoxxoEngine/Renderer/Renderer.h"
#include "FoxxoEngine/Platform/OpenGL/OpenGLShader.h"

namespace FoxxoEngine
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		FOXE_PROFILE_FUNCTION();

		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None: FOXE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererApi::Api::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}

		FOXE_CORE_ASSERT(false, "Unknown rendering api");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertSrc, const std::string& fragSrc)
	{
		FOXE_PROFILE_FUNCTION();

		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None: FOXE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererApi::Api::OpenGL: return std::make_shared<OpenGLShader>(name, vertSrc, fragSrc);
		}

		FOXE_CORE_ASSERT(false, "Unknown rendering api");
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		FOXE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
#if FOXE_PROFILE_RENDER_DETAIL == 1
		FOXE_PROFILE_FUNCTION();
#endif

		auto shader = Shader::Create(filepath);
		Add(shader);

		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
#if FOXE_PROFILE_RENDER_DETAIL == 1
		FOXE_PROFILE_FUNCTION();
#endif

		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		FOXE_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}