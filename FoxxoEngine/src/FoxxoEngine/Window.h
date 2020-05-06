#pragma once
#include "foxepch.h"

#include "FoxxoEngine/Core.h"
#include "FoxxoEngine/Event/Event.h"

namespace FoxxoEngine
{
	struct WindowProps
	{
		std::string m_Title;
		unsigned int m_Width, m_Height;

		WindowProps(const std::string& title = "FoxxoEngine", unsigned int width = 1280u, unsigned int height = 720u)
			: m_Title(title), m_Width(width), m_Height(height) {}
	};

	struct Window
	{
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetHandle() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}