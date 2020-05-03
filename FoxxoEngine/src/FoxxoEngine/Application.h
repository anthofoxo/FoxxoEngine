#pragma once

#include "Core.h"
#include "Window.h"

#include "Event/ApplicationEvent.h"

namespace FoxxoEngine
{
	class FOXE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event &e);
	private:
		bool onWindowClose(WindowCloseEvent &e);

		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};

	// To be defined in client
	Application* createApplication();
}