#pragma once

#include "FoxxoEngine.h"

class Sandbox2D : public FoxxoEngine::Layer
{
public:
	Sandbox2D()
		: Layer("Sandbox2D"), m_Camera(1280.0f / 720.0f, true) {}
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnGuiRender() override;
	virtual void OnEvent(FoxxoEngine::Event& e) override;
private:
	FoxxoEngine::Ref<FoxxoEngine::Shader> m_Shader;
	FoxxoEngine::Ref<FoxxoEngine::VertexArray> m_VertexArray;
	FoxxoEngine::Ref<FoxxoEngine::VertexBuffer> m_VertexBuffer;
	FoxxoEngine::Ref<FoxxoEngine::IndexBuffer> m_IndexBuffer;
	glm::vec4 m_Color = { 1.0f, 0.5f, 0.0f, 1.0f };

	FoxxoEngine::OrthoCameraController m_Camera;
};