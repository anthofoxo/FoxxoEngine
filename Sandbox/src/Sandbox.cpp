#include "FoxxoEngine.h"

class ExampleLayer : public FoxxoEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	std::shared_ptr<FoxxoEngine::Shader> m_shader;
	std::shared_ptr<FoxxoEngine::VertexBuffer> m_vbo;
	std::shared_ptr<FoxxoEngine::IndexBuffer> m_ibo;
	std::shared_ptr<FoxxoEngine::VertexArray> m_vao;

	void OnAttach() override
	{
		std::string vertSrc = R"(#version 330 core

layout (location = 0) in vec3 vert_pos;

void main()
{
	gl_Position = vec4(vert_pos, 1.0);
})";
		std::string fragSrc = R"(#version 330 core

layout (location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(1.0, 0.0, 0.0, 1.0);
})";

		m_shader = std::make_unique<FoxxoEngine::Shader>(vertSrc, fragSrc);

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

		m_vao.reset(FoxxoEngine::VertexArray::create());

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

		FoxxoEngine::Renderer::BeginScene();
		m_shader->Bind();
		FoxxoEngine::Renderer::Submit(m_vao);
		FoxxoEngine::Renderer::EndScene();
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