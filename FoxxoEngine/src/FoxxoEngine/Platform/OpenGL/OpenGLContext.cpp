#include "foxepch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define FOXE_STORE_STRING_PROP(x) m_RendererProperties[#x] = (const char*) glGetString(x)

namespace FoxxoEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window) {}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		FOXE_CORE_ASSERT(status, "Failed to initialize Glad!");

		FOXE_STORE_STRING_PROP(GL_VENDOR);
		FOXE_STORE_STRING_PROP(GL_RENDERER);
		FOXE_STORE_STRING_PROP(GL_VERSION);
		FOXE_STORE_STRING_PROP(GL_SHADING_LANGUAGE_VERSION);

		FOXE_CORE_INFO("GL_VENDOR: {0}", m_RendererProperties["GL_VENDOR"]);
		FOXE_CORE_INFO("GL_RENDERER: {0}", m_RendererProperties["GL_RENDERER"]);
		FOXE_CORE_INFO("GL_VERSION: {0}", m_RendererProperties["GL_VERSION"]);
		FOXE_CORE_INFO("GL_SHADING_LANGUAGE_VERSION: {0}", m_RendererProperties["GL_SHADING_LANGUAGE_VERSION"]);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}