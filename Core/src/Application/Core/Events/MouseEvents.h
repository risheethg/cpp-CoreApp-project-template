#pragma once

#include "Event.h"

namespace Project {

	class MouseMoveEvent : public Event {
	public:
		MouseMoveEvent(int x, int y) : m_X(x), m_Y(y) {}

		int GetX() const { return m_X; }
		int GetY() const { return m_Y; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMoveEvent : " << m_X << ", " << m_Y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMove)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		int m_X, m_Y;
	};

	class MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(double xOffset, double yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		const double GetXOffset() const { return m_XOffset; }
		const double GetYOffset() const { return m_XOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrollEvent : " << m_XOffset << m_XOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScroll)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryInput)
	private:
		double m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event {
	public:
		MouseButtonEvent(int keyCode) : m_KeyCode(keyCode) {}

		int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)
	protected:
		int m_KeyCode;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int keyCode) : MouseButtonEvent(keyCode) {}

		int GetKeyCode() const { return m_KeyCode; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent : " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int keyCode) : MouseButtonEvent(keyCode) {}

		int GetKeyCode() const { return m_KeyCode; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent : " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
	;
}