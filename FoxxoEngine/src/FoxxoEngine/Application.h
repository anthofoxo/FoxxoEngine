#pragma once

#include "Core.h"

namespace FoxxoEngine
{
	class FOXE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// To be defined in client
	Application* createApplication();
}