#include "foxepch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace FoxxoEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
		: m_windowHandle(windowHandle)
	{
	}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		FOXE_CORE_ASSERT(status, "Failed to initialize Glad!");

		FOXE_CORE_INFO("GL_VENDOR: {0}", glGetString(GL_VENDOR));
		FOXE_CORE_INFO("GL_RENDERER: {0}", glGetString(GL_RENDERER));
		FOXE_CORE_INFO("GL_VERSION: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}