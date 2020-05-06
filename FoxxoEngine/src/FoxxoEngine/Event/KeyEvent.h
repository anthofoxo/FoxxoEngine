#pragma once

#include "Event.h"

namespace FoxxoEngine
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_Keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
	protected:
		KeyEvent(int keycode)
			: m_Keycode(keycode)
		{}

		int m_Keycode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	private:
		int m_RepeatCount;
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount)
		{}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_Keycode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_Keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_Keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};
}