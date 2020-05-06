#include "foxepch.h"
#include "Application.h"

#include "FoxxoEngine/Event/Event.h"
#include "FoxxoEngine/Event/ApplicationEvent.h"
#include "Input.h"
#include "Renderer/Renderer.h"

#include <glad/glad.h>

namespace FoxxoEngine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application *Application::s_instance = nullptr;

	static GLenum ShaderDataTypeGLType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat2:		return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}

		FOXE_CORE_ASSERT(false, "Unknown shader datatype");
		return 0;
	}

	Application::Application()
	{
		FOXE_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));

		m_imGuiLayer = new ImGuiLayer();
		pushOverlay(m_imGuiLayer);

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

		BufferLayout layout = {
			{ShaderDataType::Float3, "position"}
		};

		using namespace RC;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		m_vbo.reset(Buffer::create(FOXE_ARRAY_BUFFER, FOXE_STATIC_DRAW, vertices, sizeof(vertices)));
		m_vbo->SetLayout(layout);

		uint32_t index = 0;
		for (const auto &element : layout)
		{
			glVertexAttribPointer(index, ShaderDataTypeCount(element.Type), ShaderDataTypeGLType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.m_stride, (const void*)element.Offset);
			glEnableVertexAttribArray(index);

			++index;
		}


		m_ibo.reset(Buffer::create(FOXE_ELEMENT_ARRAY_BUFFER, FOXE_STATIC_DRAW, indices, sizeof(indices)));

	

	}

	Application::~Application()
	{
		glDeleteVertexArrays(1, &vao);
	}

	void Application::pushLayer(Layer *layer)
	{
		m_layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer *overlay)
	{
		m_layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	bool Application::onWindowClose(WindowCloseEvent &e)
	{
		m_running = false;
		return true;
	}

	void Application::onEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		FOXE_CORE_TRACE("{0}", e);

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (e.m_handled)
				break;
		}
	}

	void Application::run()
	{
		while (m_running)
		{
			// THIS IS BAD DONT DO THIS
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader->bind();
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			for (Layer *layer : m_layerStack)
				layer->onUpdate();

			m_imGuiLayer->begin();
			for (Layer *layer : m_layerStack)
				layer->onImGuiRender();
			m_imGuiLayer->end();

			//auto [x, y] = Input::getMousePos();
		//	FOXE_CORE_TRACE("{0}, {1}", x, y);

			m_window->onUpdate();
		}
	}
}