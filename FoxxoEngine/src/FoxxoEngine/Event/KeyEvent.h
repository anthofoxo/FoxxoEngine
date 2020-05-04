#pragma once

#include "Event.h"

namespace FoxxoEngine
{
	class KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return m_keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
	protected:
		KeyEvent(int keycode)
			: m_keycode(keycode)
		{}

		int m_keycode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_repeatCount(repeatCount)
		{}

		inline int getRepeatCount() const { return m_repeatCount; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keycode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	private:
		int m_repeatCount;
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode)
		{}


		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode)
		{}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};
}