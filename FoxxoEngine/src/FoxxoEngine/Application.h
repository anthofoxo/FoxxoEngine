#pragma once

#include "Core.h"
#include "Window.h"
#include "FoxxoEngine/LayerStack.h"
#include "FoxxoEngine/Event/Event.h"
#include "FoxxoEngine/Event/ApplicationEvent.h"
#include "FoxxoEngine/ImGui/ImGuiLayer.h"

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

		inline double GetDeltaTime() const { return m_Delta; }
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() const { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		double m_Delta;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}