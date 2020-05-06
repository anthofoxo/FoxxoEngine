#pragma once

#include "Core.h"
#include "Window.h"
#include "FoxxoEngine/LayerStack.h"
#include "FoxxoEngine/Event/Event.h"
#include "FoxxoEngine/Event/ApplicationEvent.h"
#include "FoxxoEngine/ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

namespace FoxxoEngine
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() const { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer *m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<Buffer> m_vbo;
		std::shared_ptr<Buffer> m_ibo;
		std::shared_ptr<VertexArray> m_vao;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}