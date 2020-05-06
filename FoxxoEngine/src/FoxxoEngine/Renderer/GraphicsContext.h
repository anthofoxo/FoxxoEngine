#pragma once

namespace FoxxoEngine
{
	struct GraphicsContext
	{
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}