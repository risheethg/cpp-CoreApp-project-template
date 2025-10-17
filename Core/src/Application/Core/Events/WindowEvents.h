#pragma once

#include "Event.h"

namespace Project {

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowCloseEvent!";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent : " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowMoveEvent : public Event {
	public:
		WindowMoveEvent(unsigned int xmove, unsigned int ymove) : m_WindowMoveX(xmove), m_WindowMoveY(ymove) {}

		unsigned int GetXMove() const { return m_WindowMoveX; }
		unsigned int GetYMove() const { return m_WindowMoveY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowMoveEvent : " << m_WindowMoveX << m_WindowMoveY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowMove)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_WindowMoveX, m_WindowMoveY;
	};

}