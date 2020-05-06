#include "foxepch.h"
#include "WindowsInput.h"

#include "FoxxoEngine/Application.h"

#include <GLFW/glfw3.h>

#define WIN_PTR static_cast<GLFWwindow*>(Application::Get().GetWindow().GetHandle())

namespace FoxxoEngine
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode) const
	{
		auto window = WIN_PTR;
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const
	{
		auto window = WIN_PTR;
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl() const
	{
		auto window = WIN_PTR;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return {(float) x, (float) y};
	}

	float WindowsInput::GetMouseXImpl() const
	{
		auto[x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl() const
	{
		auto[x, y] = GetMousePosImpl();
		return y;
	}
}