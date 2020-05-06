#include "FoxxoEngine.h"

class ExampleLayer : public FoxxoEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
	}

	void OnEvent(FoxxoEngine::Event &e) override
	{
	}
};

class Sandbox : public FoxxoEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

FoxxoEngine::Application* FoxxoEngine::CreateApplication()
{
	return new Sandbox();
}