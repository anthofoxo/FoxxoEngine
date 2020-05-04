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

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;

		void begin();
		void end();
	private:
		float m_time = 0.0f;
	};
}