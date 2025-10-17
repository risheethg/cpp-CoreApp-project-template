#pragma once

#include "pch.h"

#define BIT(x) (1<<x)

namespace Project {

	enum class EventType : unsigned char {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMove,
		MouseButtonPressed, MouseButtonReleased, MouseMove, MouseScroll,
		KeyPressed, KeyReleased, KeyRepeat
	};

	enum EventCategory {
		EventCategoryApplication=	BIT(1),
		EventCategoryInput =		BIT(2),
		EventCategoryMouse =		BIT(3),
		EventCategoryMouseButton =	BIT(4),
		EventCategoryKeyboard =		BIT(5)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
								virtual EventType GetEventType() const override { return GetStaticType(); } \
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategoryFlags() const override { return category; }

	class Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetEventCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }	

		bool IsInCategory(int category) {
			return GetEventCategoryFlags() * category;
		}

		bool m_Handled = false;
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {
		}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator << (std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}

