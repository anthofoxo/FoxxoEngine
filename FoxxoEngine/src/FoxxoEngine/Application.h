#pragma once

#include "Core.h"
#include "Window.h"
#include "FoxxoEngine/LayerStack.h"
#include "FoxxoEngine/Event/Event.h"
#include "FoxxoEngine/Event/ApplicationEvent.h"

namespace FoxxoEngine
{
	class FOXE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event &e);

		void pushLayer(Layer *layer);
		void pushOverlay(Layer *layer);
	private:
		bool onWindowClose(WindowCloseEvent &e);

		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layerStack;
	};

	// To be defined in client
	Application* createApplication();
}