#pragma once

#include <GLFW/glfw3.h>
#include "FoxxoEngine/Core/Window.h"
#include "FoxxoEngine/Renderer/GraphicsContext.h"

namespace FoxxoEngine
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		inline virtual unsigned int GetWidth() const override { return m_Data.m_Width; }
		inline virtual unsigned int GetHeight() const override { return m_Data.m_Height; }

		inline virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual GraphicsContext& GetGraphicsContext() const override { return *m_Context; }

		inline virtual void* GetHandle() const { return m_Handle; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* m_Handle;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string m_Title;
			unsigned int m_Width, m_Height;
			bool m_Vsync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}