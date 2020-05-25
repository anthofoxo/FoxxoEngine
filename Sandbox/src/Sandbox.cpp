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

	FoxxoEngine::Ref<FoxxoEngine::Shader> m_quad_shader;
	FoxxoEngine::Ref<FoxxoEngine::Shader> m_tri_shader;
	FoxxoEngine::Ref<FoxxoEngine::Shader> m_tex_shader;
	FoxxoEngine::Ref<FoxxoEngine::VertexBuffer> m_tri_vbo;
	FoxxoEngine::Ref<FoxxoEngine::IndexBuffer> m_tri_ibo;
	FoxxoEngine::Ref<FoxxoEngine::VertexArray> m_tri_vao;
	FoxxoEngine::Ref<FoxxoEngine::VertexBuffer> m_quad_vbo;
	FoxxoEngine::Ref<FoxxoEngine::IndexBuffer> m_quad_ibo;
	FoxxoEngine::Ref<FoxxoEngine::VertexArray> m_quad_vao;
	FoxxoEngine::Ref<FoxxoEngine::Texture2D> m_texture;
	FoxxoEngine::OrthoCamera m_Camera;
	float m_CameraSpeed = 0.1f;

	glm::vec3 m_Position = glm::vec3();
	glm::vec3 m_Color = { 1.0f, 0.0f, 0.0f };

	void OnAttach() override
	{
		m_tex_shader.reset(FoxxoEngine::Shader::Create("assets/shaders/texture.glsl"));

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

			m_tri_shader.reset(FoxxoEngine::Shader::Create(vertSrc, fragSrc));

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

			m_quad_shader.reset(FoxxoEngine::Shader::Create(vertSrc, fragSrc));

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

		std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(m_tex_shader)->Bind();
		std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(m_tex_shader)->UploadUniform1i("u_texture", 0);

		m_texture = FoxxoEngine::Texture2D::Create("assets/textures/test.png");
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

		std::dynamic_pointer_cast<FoxxoEngine::OpenGLShader>(m_tex_shader)->Bind();
		FoxxoEngine::Renderer::Submit(m_tex_shader, m_tri_vao);

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