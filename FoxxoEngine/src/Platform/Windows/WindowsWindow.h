#pragma once

#include "FoxxoEngine/Window.h"
#include <GLFW/glfw3.h>

namespace FoxxoEngine
{

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps &props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_data.m_width; }
		inline unsigned int getHeight() const override { return m_data.m_height; }

		// attributes
		inline void setEventCallback(const EventCallbackFn &callback) override { m_data.m_eventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

		inline virtual void *getNativeWindow() const { return m_window; }
	private:
		virtual void init(const WindowProps &props);
		virtual void shutdown();
	private:
		GLFWwindow *m_window;

		struct WindowData
		{
			std::string m_title;
			unsigned int m_width, m_height;
			bool m_vsync;

			EventCallbackFn m_eventCallback;
		};

		WindowData m_data;
	};
}