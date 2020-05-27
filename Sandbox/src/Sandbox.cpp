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
		: Layer("Example"), m_Camera(1280.0f / 720.0f, true) {}

	FoxxoEngine::Ref<FoxxoEngine::Shader> m_quad_shader;
	FoxxoEngine::Ref<FoxxoEngine::Shader> m_tri_shader;
	//FoxxoEngine::Ref<FoxxoEngine::Shader> m_tex_shader;
	FoxxoEngine::Ref<FoxxoEngine::VertexBuffer> m_tri_vbo;
	FoxxoEngine::Ref<FoxxoEngine::IndexBuffer> m_tri_ibo;
	FoxxoEngine::Ref<FoxxoEngine::VertexArray> m_tri_vao;
	FoxxoEngine::Ref<FoxxoEngine::VertexBuffer> m_quad_vbo;
	FoxxoEngine::Ref<FoxxoEngine::IndexBuffer> m_quad_ibo;
	FoxxoEngine::Ref<FoxxoEngine::VertexArray> m_quad_vao;
	FoxxoEngine::Ref<FoxxoEngine::Texture2D> m_texture;
	FoxxoEngine::OrthoCameraController m_Camera;

	glm::vec3 m_Position = glm::vec3();
	glm::vec3 m_Color = { 1.0f, 0.0f, 0.0f };

	FoxxoEngine::ShaderLibrary m_ShaderLibrary;

	void OnAttach() override
	{
		{
			std::string vertSrc = R"(
#version 330 core

layout (location = 0) in vec3 vert_pos;

out vec3 frag_color;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(vert_pos, 1.0);
	frag_color = vert_pos * 0.5 + 0.5;
})";
			std::string fragSrc = R"(
#version 330 core

in vec3 frag_color;

layout (location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(frag_color, 1.0);
})";

			m_tri_shader = FoxxoEngine::Shader::Create("TriangleShader", vertSrc, fragSrc);

			float vertices[] =
			{
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
			};

			unsigned int indices[] =
			{
				0, 1, 2, 2, 3, 0
			};

			m_tri_vao.reset(FoxxoEngine::VertexArray::Create());

			FoxxoEngine::BufferLayout layout = {
				{FoxxoEngine::ShaderDataType::Float3, "position"},
				{FoxxoEngine::ShaderDataType::Float2, "texCoord"}
			};

			m_tri_vbo.reset(FoxxoEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
			m_tri_vbo->SetLayout(layout);

			m_tri_ibo.reset(FoxxoEngine::IndexBuffer::Create(indices, sizeof(indices)));

			m_tri_vao->AddVertexBuffer(m_tri_vbo);
			m_tri_vao->SetIndexBuffer(m_tri_ibo);
		}

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

uniform vec3 u_Color;

layout (location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(u_Color, 1.0);
})";

			m_quad_shader = FoxxoEngine::Shader::Create("QuadShader", vertSrc, fragSrc);

			float vertices[] =
			{
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				-0.5f, 0.5f, 0.0f
			};

			unsigned int indices[] =
			{
				0, 1, 2, 2, 3, 0
			};

			m_quad_vao.reset(FoxxoEngine::VertexArray::Create());

			FoxxoEngine::BufferLayout layout = {
				{FoxxoEngine::ShaderDataType::Float3, "position"}
			};

			m_quad_vbo.reset(FoxxoEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
			m_quad_vbo->SetLayout(layout);

			m_quad_ibo.reset(FoxxoEngine::IndexBuffer::Create(indices, sizeof(indices)));

			m_quad_vao->AddVertexBuffer(m_quad_vbo);
			m_quad_vao->SetIndexBuffer(m_quad_ibo);
		}

		auto shader = m_ShaderLibrary.Load("assets/shaders/texture.glsl");
		//m_tex_shader = FoxxoEngine::Shader::Create("assets/shaders/texture.glsl");
		std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(shader)->Bind();
		std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(shader)->UploadUniform1i("u_texture", 0);

		m_texture = FoxxoEngine::Texture2D::Create("assets/textures/test.png");
	}

	void OnDetach() override
	{
	}

	void OnUpdate() override
	{
		m_Camera.OnUpdate();

		//FoxxoEngine::RenderCommand::SetClearColor({ 1, 0, 1, 1 });
		FoxxoEngine::RenderCommand::SetClearColor({ 0, 0, 0, 1 });
		FoxxoEngine::RenderCommand::Clear();

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		FoxxoEngine::Renderer::BeginScene(m_Camera.GetCamera());

		std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(m_quad_shader)->Bind();
		std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(m_quad_shader)->UploadUniform3f("u_Color", m_Color);

		for (int y = 0; y < 5; ++y)
		{
			for (int x = 0; x < 5; ++x)
			{
				glm::vec3 pos = glm::vec3(float(x), float(y), 0.0f) * 0.2f;
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position + pos) * scale;

				FoxxoEngine::Renderer::Submit(m_quad_shader, m_quad_vao, transform);
			}
		}

		//std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(m_tri_shader)->Bind();
		//FoxxoEngine::Renderer::Submit(m_tri_shader, m_tri_vao);

		m_texture->Bind();

		auto shader = m_ShaderLibrary.Get("texture");
		//std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(m_tex_shader)->Bind();
		std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(shader)->Bind();
		FoxxoEngine::Renderer::Submit(shader, m_tri_vao);

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

		double deltatime = FoxxoEngine::Application::Get().GetDeltaTime();

		std::stringstream ss;
		ss << "FPS: " << int(1.f / deltatime);
		ImGui::Text(ss.str().c_str());

		ImGui::End();
	}

	void OnEvent(FoxxoEngine::Event& e) override
	{
		m_Camera.OnEvent(e);
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