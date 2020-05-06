#include "FoxxoEngine.h"

class ExampleLayer : public FoxxoEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void onUpdate() override
	{
	}

	void onEvent(FoxxoEngine::Event &e) override
	{
	}
};

class Sandbox : public FoxxoEngine::Application
{
public:
	Sandbox()
	{
		pushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

FoxxoEngine::Application* FoxxoEngine::createApplication()
{
	return new Sandbox();
}