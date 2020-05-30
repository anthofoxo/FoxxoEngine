#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "FoxxoEngine/Platform/OpenGL/OpenGLShader.h"

static FoxxoEngine::Ref<FoxxoEngine::Texture2D> texture;

void Sandbox2D::OnAttach()
{
	texture = FoxxoEngine::Texture2D::Create("assets/textures/test.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate()
{
	m_Camera.OnUpdate();

	FoxxoEngine::Renderer2D::BeginScene(m_Camera.GetCamera());

	for (int y = -5; y <= 5; ++y)
		for (int x = -5; x <= 5; ++x)
			FoxxoEngine::Renderer2D::DrawQuad({ x, y }, { 0.5f, 0.5f }, texture);

	FoxxoEngine::Renderer2D::EndScene();
}

void Sandbox2D::OnGuiRender()
{
	ImGui::Begin("Render Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::ColorEdit4("Quad Color", glm::value_ptr(m_Color));
	ImGui::End();

	auto properties = FoxxoEngine::Application::Get().GetWindow().GetGraphicsContext().m_RendererProperties;
	ImGui::Begin("Context Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	for (const auto [x, y] : properties)
	{
		std::stringstream ss;
		ss << x << ": " << y;
		ImGui::Text(ss.str().c_str());
	}

	double deltatime = FoxxoEngine::Application::Get().GetDeltaTime();

	std::stringstream ss;
	ss << "FPS: " << int(1.f / deltatime);
	ImGui::Text(ss.str().c_str());

	ImGui::End();
}

void Sandbox2D::OnEvent(FoxxoEngine::Event& e)
{
	m_Camera.OnEvent(e);
}