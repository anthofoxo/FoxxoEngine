#pragma once

#include "foxepch.h"

#include "FoxxoEngine/Core.h"
#include "FoxxoEngine/Event/Event.h"

namespace FoxxoEngine
{
	struct WindowProps
	{
		std::string m_title;
		unsigned int m_width, m_height;

		WindowProps(const std::string &title = "FoxxoEngine", unsigned int width = 1280, unsigned int height = 720)
			: m_title(title), m_width(width), m_height(height)
		{
		}
	};

	// Interface representing a desktop system based window
	class FOXE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event &)>;

		virtual ~Window()
		{};

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// attributes
		virtual void setEventCallback(const EventCallbackFn &callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Window* create(const WindowProps &props = WindowProps());
	};
}