#pragma once


namespace FoxxoEngine
{
	namespace RendererConstants
	{
		extern uint32_t FOXE_ARRAY_BUFFER;
		extern uint32_t FOXE_ELEMENT_ARRAY_BUFFER;
		extern uint32_t FOXE_STATIC_DRAW;
	}

	namespace RC = RendererConstants;

	enum struct RendererAPI
	{
		None, OpenGL
	};

	struct Renderer
	{
		inline static RendererAPI getAPI() { return api; }

		static RendererAPI api;
	};
}