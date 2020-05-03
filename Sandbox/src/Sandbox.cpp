#include "FoxxoEngine.h"

class Sandbox : public FoxxoEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

FoxxoEngine::Application* FoxxoEngine::createApplication()
{
	return new Sandbox();
}