#pragma once

#ifdef FOXE_PLATFORM_WINDOWS

extern FoxxoEngine::Application* FoxxoEngine::createApplication();

int main(int argc, char **argv)
{
	FoxxoEngine::Log::init();
	FOXE_CORE_WARN("Initialized Log!");
	FOXE_INFO("Initialized Log!");

	auto app = FoxxoEngine::createApplication();
	app->run();
	delete app;
}

#endif