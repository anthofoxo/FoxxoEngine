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
		FOXE_INFO("ExampleLayer::Update");
	}

	void onEvent(FoxxoEngine::Event &e) override
	{
		FOXE_TRACE("{0}", e);
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