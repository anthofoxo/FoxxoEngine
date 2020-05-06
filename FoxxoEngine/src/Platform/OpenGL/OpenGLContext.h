#pragma once

#include "FoxxoEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace FoxxoEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow *windowHandle);

		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow *m_windowHandle;
	};
}