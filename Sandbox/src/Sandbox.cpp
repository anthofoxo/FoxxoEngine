#include "foxepch.h"
#include "FoxxoEngine.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "FoxxoEngine/Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

class ExampleLayer : public FoxxoEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {}

	FoxxoEngine::Ref<FoxxoEngine::Shader> m_shader;
	FoxxoEngine::Ref<FoxxoEngine::VertexBuffer> m_vbo;
	FoxxoEngine::Ref<FoxxoEngine::IndexBuffer> m_ibo;
	FoxxoEngine::Ref<FoxxoEngine::VertexArray> m_vao;
	FoxxoEngine::OrthoCamera m_Camera;
	float m_CameraSpeed = 0.1f;

	glm::vec3 m_Position = glm::vec3();
	glm::vec3 m_Color = { 1.0f, 0.0f, 0.0f };

	void OnAttach() override
	{
		std::string vertSrc = R"(
#version 330 core

layout (location = 0) in vec3 vert_pos;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(vert_pos, 1.0);
})";
		std::string fragSrc = R"(
#version 330 core

layout (location = 0) out vec4 out_color;

uniform vec3 u_Color;

void main()
{
	out_color = vec4(u_Color, 1.0);
})";

		m_shader.reset(FoxxoEngine::Shader::Create(vertSrc, fragSrc));

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		unsigned int indices[] =
		{
			0, 1, 2
		};

		m_vao.reset(FoxxoEngine::VertexArray::Create());

		FoxxoEngine::BufferLayout layout = {
			{FoxxoEngine::ShaderDataType::Float3, "position"}
		};

		m_vbo.reset(FoxxoEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_vbo->SetLayout(layout);

		m_ibo.reset(FoxxoEngine::IndexBuffer::Create(indices, sizeof(indices)));

		m_vao->AddVertexBuffer(m_vbo);
		m_vao->SetIndexBuffer(m_ibo);
	}

	void OnDetach() override
	{
	}

	void OnUpdate() override
	{
		{
			static glm::vec3 pos = glm::vec3();
			static float rot = 0.0f;

			double deltatime = FoxxoEngine::Application::Get().GetDeltaTime();

			FOXE_INFO("Frametime: {1} FPS, {0} Seconds", deltatime, int(1.f / deltatime));

			float m_CameraMoveSpeed = 1.f * (float) deltatime;
			float m_CameraRotSpeed = 10.f * (float) deltatime;

			if (FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_A) | FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_LEFT))
				pos.x -= m_CameraMoveSpeed;

			if (FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_D) | FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_RIGHT))
				pos.x += m_CameraMoveSpeed;

			if (FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_S) | FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_DOWN))
				pos.y -= m_CameraMoveSpeed;

			if (FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_W) | FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_UP))
				pos.y += m_CameraMoveSpeed;

			if (FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_Q))
				rot += m_CameraRotSpeed;

			if (FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_E))
				rot -= m_CameraRotSpeed;

			m_Camera.SetPosition(pos);
			m_Camera.SetRotation(rot);

			if (FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_J))
				m_Position.x -= m_CameraMoveSpeed;

			if (FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_L))
				m_Position.x += m_CameraMoveSpeed;

			if (FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_K))
				m_Position.y -= m_CameraMoveSpeed;

			if (FoxxoEngine::Input::IsKeyPressed(FOXE_KEY_I))
				m_Position.y += m_CameraMoveSpeed;
		}

		//FoxxoEngine::RenderCommand::SetClearColor({ 1, 0, 1, 1 });
		FoxxoEngine::RenderCommand::SetClearColor({ 0, 0, 0, 1 });
		FoxxoEngine::RenderCommand::Clear();

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		FoxxoEngine::Renderer::BeginScene(m_Camera);

		std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(m_shader)->Bind();
		std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(m_shader)->UploadUniform3f("u_Color", m_Color);

		for (int y = 0; y < 5; ++y)
		{
			for (int x = 0; x < 5; ++x)
			{
				glm::vec3 pos = glm::vec3(float(x), float(y), 0.0f) * 0.2f;
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position + pos) * scale;

				FoxxoEngine::Renderer::Submit(m_shader, m_vao, transform);
			}
		}

		FoxxoEngine::Renderer::EndScene();
	}

	void OnGuiRender()
	{
		ImGui::Begin("Render Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::ColorEdit3("Triangles Color", glm::value_ptr(m_Color));
		ImGui::End();

		auto properties = FoxxoEngine::Application::Get().GetWindow().GetGraphicsContext().m_RendererProperties;
		ImGui::Begin("Context Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		for (const auto [x, y] : properties)
		{
			std::stringstream ss;
			ss << x << ": " << y;
			ImGui::Text(ss.str().c_str());
		}

		ImGui::End();
	}

	void OnEvent(FoxxoEngine::Event& e) override
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