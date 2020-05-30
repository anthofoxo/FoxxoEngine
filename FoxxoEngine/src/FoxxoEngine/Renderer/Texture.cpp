#include "foxepch.h"
#include "foxepch.h"

#include "Texture.h"
#include "Renderer.h"

#include "FoxxoEngine/Platform/OpenGL/OpenGLTexture.h"

namespace FoxxoEngine
{
	Ref<Texture2D> Texture2D::Create(unsigned int width, unsigned int height, unsigned char* data)
	{
		FOXE_PROFILE_FUNCTION();

		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None: FOXE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererApi::Api::OpenGL: return std::make_shared<OpenGLTexture2D>(width, height, data);
		}

		FOXE_CORE_ASSERT(false, "Unknown rendering api");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		FOXE_PROFILE_FUNCTION();

		switch (Renderer::GetApi())
		{
			case RendererApi::Api::None: FOXE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererApi::Api::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		FOXE_CORE_ASSERT(false, "Unknown rendering api");
		return nullptr;
	}
}