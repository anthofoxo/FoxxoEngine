#include "FoxxoEngine.h"

class ExampleLayer : public FoxxoEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), camera(-1.6f, 1.6f, -0.9f, 0.9f) {}

	std::shared_ptr<FoxxoEngine::Shader> m_shader;
	std::shared_ptr<FoxxoEngine::VertexBuffer> m_vbo;
	std::shared_ptr<FoxxoEngine::IndexBuffer> m_ibo;
	std::shared_ptr<FoxxoEngine::VertexArray> m_vao;
	FoxxoEngine::OrthoCamera camera;

	void OnAttach() override
	{
		std::string vertSrc = R"(
#version 330 core

layout (location = 0) in vec3 vert_pos;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	gl_Position = u_Projection * u_View * vec4(vert_pos, 1.0);
})";
		std::string fragSrc = R"(
#version 330 core

layout (location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(1.0, 0.0, 0.0, 1.0);
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
		FoxxoEngine::RenderCommand::SetClearColor({ 1, 0, 1, 1 });
		FoxxoEngine::RenderCommand::Clear();

		camera.SetPosition({ -0.5f, 0.0f, 0.0f });

		FoxxoEngine::Renderer::BeginScene(camera);
		FoxxoEngine::Renderer::Submit(m_shader, m_vao);
		FoxxoEngine::Renderer::EndScene();
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