#include "foxepch.h"
#include "WindowsWindow.h"

#include "FoxxoEngine/Event/Event.h"
#include "FoxxoEngine/Event/ApplicationEvent.h"
#include "FoxxoEngine/Event/KeyEvent.h"
#include "FoxxoEngine/Event/MouseEvent.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace FoxxoEngine
{
	static bool s_GLFWInitialized = false;

	static void GLFWerrorCallback(int error, const char *description)
	{
		FOXE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::create(const WindowProps &props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps &props)
	{
		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::init(const WindowProps &props)
	{
		m_data.m_title = props.m_title;
		m_data.m_width = props.m_width;
		m_data.m_height = props.m_height;

		FOXE_CORE_INFO("Creating window {0} ({1}, {2})", props.m_title, props.m_width, props.m_height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfWTerminate on system shutdown
			int success = glfwInit();
			FOXE_CORE_ASSERT(success, "Could not initalize GLFW!");

			glfwSetErrorCallback(GLFWerrorCallback);

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int) props.m_width, (int) props.m_height, m_data.m_title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);

		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		FOXE_CORE_ASSERT(status, "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

		// set callbacks

		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow *window, int width, int height)
		{
			WindowData &data = *(WindowData*) glfwGetWindowUserPointer(window);
			
			data.m_width = width;
			data.m_height = height;

			WindowResizeEvent event(width, height);
			data.m_eventCallback(event);			
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window)
		{
			WindowData &data = *(WindowData*) glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.m_eventCallback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			WindowData &data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.m_eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.m_eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.m_eventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_window, [](GLFWwindow *window, unsigned int c)
		{
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
			KeyTypedEvent event(c);
			data.m_eventCallback(event);
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods)
		{
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.m_eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.m_eventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOffset, double yOffset)
		{
			WindowData &data = *(WindowData*) glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float) xOffset, (float) yOffset);
			data.m_eventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xPos, double yPos)
		{
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float) xPos, (float) yPos);
			data.m_eventCallback(event);
		});
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		glfwSwapInterval((m_data.m_vsync = enabled) ? 1 : 0);
	}

	bool WindowsWindow::isVSync() const
	{
		return m_data.m_vsync;
	}
	
	
}

