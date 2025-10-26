#include "pch.h"
#include "Window.h"

namespace Project {

	static bool s_GLFWinitialized = false;

	Window::Window(const WindowProperties& windowProps) {
		Init(windowProps);
	}

	Window::~Window() {
		Shutdown();
	}

	void Window::Init(const WindowProperties& windowProps) {
		PROJECT_CORE_INFO("Creating window with properties: {0} {1} \"{2}\" ...", windowProps.Width,
			windowProps.Height, windowProps.WindowTitle);
		m_Data.Width = windowProps.Width;
		m_Data.Height = windowProps.Height;
		m_Data.Title = windowProps.WindowTitle;

		if (!s_GLFWinitialized) {
			int success = glfwInit();
			PROJECT_CORE_ASSERT(success, "Failed to initialize GLFW");
			s_GLFWinitialized = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PROJECT_CORE_ASSERT(status, "Failed to initialize GLAD!");
		PROJECT_CORE_INFO("Window created successfuly!");
		
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			data.EventCallback(e);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMoveEvent e((int)xpos, (int)ypos);
			data.EventCallback(e);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
					{
						MouseButtonPressedEvent e(button);
						data.EventCallback(e);
						break;
					}
				case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent e(button);
						data.EventCallback(e);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent e(xoffset, yoffset);
			data.EventCallback(e);
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowResizeEvent e(width, height);
			data.EventCallback(e);
			});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowMoveEvent e(xpos, ypos);
			data.EventCallback(e);
			});
	}

	void Window::Shutdown() {
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}
