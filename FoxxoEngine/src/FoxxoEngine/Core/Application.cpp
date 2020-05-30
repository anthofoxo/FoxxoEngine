#include "foxepch.h"
#include "Application.h"

#include "FoxxoEngine/Event/Event.h"
#include "FoxxoEngine/Event/ApplicationEvent.h"
#include "FoxxoEngine/Core/Input.h"
#include "FoxxoEngine/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace FoxxoEngine
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FOXE_PROFILE_FUNCTION();

		FOXE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
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

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::Run()
	{
		FOXE_PROFILE_FUNCTION();

		while (m_Running)
		{
			FOXE_PROFILE_SCOPE("Runloop");

			double time = glfwGetTime();
			static double lastTime = time;
			m_Delta = time - lastTime;
			lastTime = time;

			if (!m_Minimized)
			{
				FOXE_PROFILE_SCOPE("Layerstack update");

				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();

			{
				FOXE_PROFILE_SCOPE("Layerstack gui update");

				for (Layer* layer : m_LayerStack)
					layer->OnGuiRender();
			}

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}