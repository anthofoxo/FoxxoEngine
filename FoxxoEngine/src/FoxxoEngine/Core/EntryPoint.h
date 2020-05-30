#pragma once

#ifdef FOXE_PLATFORM_WINDOWS

extern FoxxoEngine::Application* FoxxoEngine::CreateApplication();

int main(int argc, char** argv)
{
	FoxxoEngine::Log::Init();
	FOXE_CORE_INFO("Initialized Log!");
	FOXE_INFO("Initialized Log!");

	FOXE_PROFILE_BEGIN_SESSION("Startup", "FoxxoEngineProfile-Startup.json");
	auto app = FoxxoEngine::CreateApplication();
	FOXE_PROFILE_END_SESSION();

	FOXE_PROFILE_BEGIN_SESSION("Runtime", "FoxxoEngineProfile-Runtime.json");
	app->Run();
	FOXE_PROFILE_END_SESSION();

	FOXE_PROFILE_BEGIN_SESSION("Shutdown", "FoxxoEngineProfile-Shutdown.json");
	delete app;
	FOXE_PROFILE_END_SESSION();
}

#endif