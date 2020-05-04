#pragma once

#include "foxepch.h"
#include "FoxxoEngine/Core.h"
#include "Layer.h"

namespace FoxxoEngine
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer *layer);
		void pushOverlay(Layer *overlay);
		void popLayer(Layer *layer);
		void popOverlay(Layer *overlay);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }
	private:
		std::vector<Layer*> m_layers;
		unsigned int m_layerInsertIndex = 0;
	};
}