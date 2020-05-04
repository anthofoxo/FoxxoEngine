#include "foxepch.h"
#include "WindowsInput.h"

#include "FoxxoEngine/Application.h"

#include <GLFW/glfw3.h>

namespace FoxxoEngine
{
	Input* Input::s_instance = new WindowsInput();

	bool WindowsInput::isKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::getMousePosImpl()
	{
		auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return {(float) x, (float) y};
	}

	float WindowsInput::getMouseXImpl()
	{
		auto[x, y] = getMousePosImpl();
		return x;
	}

	float WindowsInput::getMouseYImpl()
	{
		auto[x, y] = getMousePosImpl();
		return y;
	}
}