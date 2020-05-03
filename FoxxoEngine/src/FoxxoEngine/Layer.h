#pragma once

#include "FoxxoEngine/Core.h"
#include "FoxxoEngine/Event/Event.h"

namespace FoxxoEngine
{
	class FOXE_API Layer
	{
	public:
		Layer(const std::string &name = "layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event &e) {}

		inline const std::string& getName() const { return m_debugName; }
	private:
		std::string m_debugName;
	};
}