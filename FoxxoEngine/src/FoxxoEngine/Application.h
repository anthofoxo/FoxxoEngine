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

		void run();

		void onEvent(Event &e);

		void pushLayer(Layer *layer);
		void pushOverlay(Layer *layer);

		inline static Application& get() { return *s_instance; }
		inline Window& getWindow() const { return *m_window; }
	private:
		bool onWindowClose(WindowCloseEvent &e);

		std::unique_ptr<Window> m_window;
		ImGuiLayer *m_imGuiLayer;
		bool m_running = true;
		LayerStack m_layerStack;

		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<Buffer> m_vbo;
		std::shared_ptr<Buffer> m_ibo;
		std::shared_ptr<VertexArray> m_vao;
	private:
		static Application* s_instance;
	};

	// To be defined in client
	Application* createApplication();
}