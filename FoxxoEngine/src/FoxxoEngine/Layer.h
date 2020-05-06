#pragma once

#include "FoxxoEngine/Core.h"
#include "FoxxoEngine/Event/Event.h"

namespace FoxxoEngine
{
	struct Layer
	{
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetDebugName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}