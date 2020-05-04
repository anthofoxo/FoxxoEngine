#pragma once

#include "FoxxoEngine/Layer.h"
#include "FoxxoEngine/Event/KeyEvent.h"
#include "FoxxoEngine/Event/MouseEvent.h"
#include "FoxxoEngine/Event/ApplicationEvent.h"

namespace FoxxoEngine
{
	class FOXE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();

		void onUpdate();
		void onEvent(Event &e);
	private:
		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
		bool onMouseMoveEvent(MouseMovedEvent &e);
		bool onMouseScrollEvent(MouseScrolledEvent &e);
		bool onKeyPressEvent(KeyPressedEvent &e);
		bool onKeyReleaseEvent(KeyReleasedEvent &e);
		bool onKeyTypedEvent(KeyTypedEvent &e);
		bool onWindowResize(WindowResizeEvent &e);
	private:
		float m_time = 0.0f;
	};
}