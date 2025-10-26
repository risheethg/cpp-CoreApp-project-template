#pragma once

#include "pch.h"

#include "Core/Log.h"

#include "Application/Core/Events/Event.h"
#include "Application/Core/Events/MouseEvents.h"
#include "Application/Core/Events/WindowEvents.h"

#include "Application/Core/Window/Window.h"

#include "Application/Core/Layers/LayerStack.h"

namespace Project {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Init();
		void Shutdown();

		void Run();
		void OnEvent(Event& event);

		void PushOverlay(Layer* overlay);
		void PushLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		void PopLayer(Layer* layer);

		bool OnApplicationCloseEvent(WindowCloseEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& event);

		static inline Application& GetApplication() { return *s_Application; }
		inline const Window& GetWindow() const { return *m_Window; }
	private:
		bool m_Running = true;
		static Application* s_Application;
		Window* m_Window;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}