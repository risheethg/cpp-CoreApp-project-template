#pragma once

#include "pch.h"

#include "Core/Log.h"

#include "Application/Core/Events/Event.h"
#include "Application/Core/Events/MouseEvents.h"
#include "Application/Core/Events/WindowEvents.h"

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

		static inline Application& GetApplication() { return *s_Application; }
	private:
		bool m_Running = true;
		static Application* s_Application;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}