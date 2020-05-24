#pragma once

#include <vector>
#include <typeinfo>
#include <any>
#include <iostream>

namespace FoxxoEngine
{
	struct Event
	{
		virtual ~Event() = default;
	};

	template<typename T>
	struct EventListener
	{
		virtual ~EventListener() = default;
		virtual bool OnEvent(T* e) = 0;
	};

	struct EventDispatcher
	{
		std::vector<std::any*> m_EventListeners;

		void dispatch(const Event& e)
		{
			std::string s = typeid(e).name();

			for (std::any* listener : m_EventListeners)
			{
			}
		}
	};

	void initExample()
	{
		struct ExampleEvent : public Event
		{
			ExampleEvent(int d) : data(d) {};

			int data = 0;
		};

		struct EventListenerExample : public EventListener<ExampleEvent>
		{
			virtual bool OnEvent(ExampleEvent* e)
			{
				std::cout << e->data << std::endl;
			}
		};

		std::any instance = EventListenerExample();
		ExampleEvent event = ExampleEvent(12);

		EventDispatcher dispatcher;
		dispatcher.m_EventListeners.push_back(&instance);

		dispatcher.dispatch(event);
	}
}