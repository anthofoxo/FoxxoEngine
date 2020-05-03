#pragma once

#include "FoxxoEngine/Layer.h"

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
		float m_time = 0.0f;
	};
}