#include "foxepch.h"
#include "RenderCommand.h"

#include "FoxxoEngine/Platform/OpenGL/OpenGLRendererApi.h"

namespace FoxxoEngine
{
	RendererApi* RenderCommand::s_RendererApi = new OpenGLRendererApi();
}