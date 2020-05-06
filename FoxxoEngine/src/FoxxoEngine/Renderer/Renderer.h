#pragma once

namespace FoxxoEngine
{
	namespace RendererConstants
	{
		extern uint32_t FOXE_ARRAY_BUFFER;
		extern uint32_t FOXE_ELEMENT_ARRAY_BUFFER;
		extern uint32_t FOXE_STATIC_DRAW;
		extern uint32_t FOXE_TRIANGLES;
	}

	enum struct RendererAPI
	{
		None, OpenGL
	};

	struct Renderer
	{
		inline static RendererAPI GetAPI() { return s_Api; }

		static RendererAPI s_Api;
	};
}