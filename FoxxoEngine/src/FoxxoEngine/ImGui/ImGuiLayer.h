#pragma once

#include "FoxxoEngine/Layer.h"
#include "FoxxoEngine/Event/KeyEvent.h"
#include "FoxxoEngine/Event/MouseEvent.h"
#include "FoxxoEngine/Event/ApplicationEvent.h"

namespace FoxxoEngine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}