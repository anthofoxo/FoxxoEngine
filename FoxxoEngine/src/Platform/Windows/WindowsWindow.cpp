#include "foxepch.h"
#include "WindowsWindow.h"

namespace FoxxoEngine
{
	static bool s_GLFWInitialized = false;

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

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int) props.m_width, (int) props.m_height, m_data.m_title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);
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

