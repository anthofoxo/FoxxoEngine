#include "foxepch.h"
#include "Application.h"

#include "FoxxoEngine/Event/ApplicationEvent.h"
#include "FoxxoEngine/Log.h"

namespace FoxxoEngine
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		FOXE_TRACE(e);

		while (true);
	}
}