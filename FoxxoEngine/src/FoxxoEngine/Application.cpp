#include "foxepch.h"
#include "Application.h"

#include "FoxxoEngine/Event/Event.h"
#include "FoxxoEngine/Event/ApplicationEvent.h"
#include "FoxxoEngine/Input.h"
#include "FoxxoEngine/Renderer/Renderer.h"

#include <glad/glad.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace FoxxoEngine
{
	Application *Application::s_Instance = nullptr;

	Application::Application()
	{
		FOXE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

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

		m_shader = std::make_unique<Shader>(vertSrc, fragSrc);

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

		using namespace RendererConstants;

		m_vao.reset(VertexArray::create());
		
		BufferLayout layout = {
			{ShaderDataType::Float3, "position"}
		};

		m_vbo.reset(Buffer::Create(FOXE_ARRAY_BUFFER, FOXE_STATIC_DRAW, vertices, sizeof(vertices)));
		m_vbo->SetLayout(layout);

		m_ibo.reset(Buffer::Create(FOXE_ELEMENT_ARRAY_BUFFER, FOXE_STATIC_DRAW, indices, sizeof(indices)));

		m_vao->AddVertexBuffer(m_vbo);
		m_vao->SetIndexBuffer(m_ibo);
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		FOXE_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader->Bind();
			m_vao->Bind();
			glDrawElements(RendererConstants::FOXE_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();

			for (Layer *layer : m_LayerStack)
				layer->OnGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}