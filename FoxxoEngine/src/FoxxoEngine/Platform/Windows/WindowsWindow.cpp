#include "foxepch.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

#include "FoxxoEngine/Event/Event.h"
#include "FoxxoEngine/Event/ApplicationEvent.h"
#include "FoxxoEngine/Event/KeyEvent.h"
#include "FoxxoEngine/Event/MouseEvent.h"
#include "FoxxoEngine/Platform/Windows/WindowsInput.h"
#include "FoxxoEngine/Platform/OpenGL/OpenGLContext.h"

namespace FoxxoEngine
{
	static bool s_GlfwInitialized = false;

	static void GLFWerrorCallback(int error, const char* description)
	{
		FOXE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.m_Title = props.m_Title;
		m_Data.m_Width = props.m_Width;
		m_Data.m_Height = props.m_Height;

		FOXE_CORE_INFO("Creating window {0} ({1}, {2})", props.m_Title, props.m_Width, props.m_Height);

		if (!s_GlfwInitialized)
		{
			// TODO: glfWTerminate on system shutdown
			int success = glfwInit();
			FOXE_CORE_ASSERT(success, "Failed to initalize GLFW!");

			glfwSetErrorCallback(GLFWerrorCallback);

			s_GlfwInitialized = true;
		}

		m_Handle = glfwCreateWindow((int) props.m_Width, (int) props.m_Height, m_Data.m_Title.c_str(), nullptr, nullptr);

		FOXE_CORE_ASSERT(m_Handle, "Failed to create window!");

		m_Context = new OpenGLContext(m_Handle);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Handle, &m_Data);
		SetVSync(true);

		glfwSetFramebufferSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			data.m_Width = width;
			data.m_Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
				case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
				case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
			}
		});

		glfwSetCharCallback(m_Handle, [](GLFWwindow* window, unsigned int c)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			KeyTypedEvent event(c);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
				case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
			}
		});

		glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float) xOffset, (float) yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float) xPos, (float) yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Handle);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval((m_Data.m_Vsync = enabled) ? 1 : 0);
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.m_Vsync;
	}
}