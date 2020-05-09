#pragma once

#include <unordered_map>

namespace FoxxoEngine
{
	struct GraphicsContext
	{
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		std::unordered_map<std::string, std::string> m_RendererProperties;
	};
}