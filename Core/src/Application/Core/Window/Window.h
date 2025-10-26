#pragma once

#include "Core/Events/Event.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Events/WindowEvents.h"

namespace Project {

	struct WindowProperties {
		std::string WindowTitle;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string windowTitle = "Project Renderer", unsigned int width = 1920, unsigned int height = 1080) 
			: WindowTitle(windowTitle), Width(width), Height(height)	{}
	};

	class Window
	{
	public:
		Window(const WindowProperties& windowProps = WindowProperties());
		~Window();

		using EventCallbackFn = std::function<void(Event&)>;

		void Init(const WindowProperties& windowProps);
		void Shutdown();

		void OnUpdate();

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }
		void SetWidth(unsigned int width) { m_Width = width; }
		void SetHeight(unsigned int height) { m_Width = height; }

		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		inline GLFWwindow* GetGLFWwindow() const { return m_Window; }
	private:
		unsigned int m_Width, m_Height;
		
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool vsync = false;
			EventCallbackFn EventCallback;
		} m_Data;
	};

}