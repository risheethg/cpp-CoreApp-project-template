#include "pch.h"
#include "Application.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Project {


	Application* Application::s_Application = nullptr;

	Application::Application() {
		Init();
	}

	Application::~Application() {
		Shutdown();
	}

	void Application::Init() {
		s_Application = this;
		Log::Init();
		PROJECT_CORE_INFO("Core Has Been Initialized!");
		for (Layer* layer : m_LayerStack)
			layer->OnAttach();
	}

	void Application::Shutdown() {
	}

	void Application::Run() {
		while (m_Running) {
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		for (Layer* layer : m_LayerStack)
			layer->OnEvent(event);
		PROJECT_CORE_TRACE(event.ToString());
		EventDispatcher eventDispatcher(event);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PopOverlay(Layer* overlay) {
		m_LayerStack.PopOverlay(overlay);
	}

	void Application::PopLayer(Layer* layer) {
		m_LayerStack.PopLayer(layer);
	}

}