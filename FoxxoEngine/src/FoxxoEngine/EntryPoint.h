#pragma once

#ifdef FOXE_PLATFORM_WINDOWS

extern FoxxoEngine::Application* FoxxoEngine::createApplication();

int main(int argc, char **argv)
{
	auto app = FoxxoEngine::createApplication();
	app->run();
	delete app;
}

#endif