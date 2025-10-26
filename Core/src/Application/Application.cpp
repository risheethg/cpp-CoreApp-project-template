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
		PROJECT_CORE_INFO("Application Has been Initialized!");
		m_Window = new Window();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		for (Layer* layer : m_LayerStack)
			layer->OnAttach();
	}

	void Application::Shutdown() {
		delete m_Window;
	}

	void Application::Run() {
		while (m_Running) {
			glClearColor(0.8f, 0.0f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		for (Layer* layer : m_LayerStack)
			layer->OnEvent(event);
		PROJECT_CORE_TRACE(event.ToString());
		EventDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnApplicationCloseEvent));
		eventDispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResizeEvent));
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

	bool Application::OnApplicationCloseEvent(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResizeEvent(WindowResizeEvent& event) {
		m_Window->SetWidth(event.GetWidth());
		m_Window->SetHeight(event.GetHeight());
		return true;
	}

}