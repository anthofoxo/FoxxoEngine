#pragma once

#ifdef FOXE_PLATFORM_WINDOWS

extern FoxxoEngine::Application* FoxxoEngine::CreateApplication();

int main(int argc, char** argv)
{
	FoxxoEngine::Log::Init();
	FOXE_CORE_INFO("Initialized Log!");
	FOXE_INFO("Initialized Log!");

	auto app = FoxxoEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif