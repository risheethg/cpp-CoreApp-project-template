#include "pch.h"
#include "ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Application.h"

namespace Project {

	ImGuiLayer::ImGuiLayer(const std::string& name) : Layer(name) {
	}

	ImGuiLayer::~ImGuiLayer() {
	}

	void ImGuiLayer::OnAttach() {

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // If using Docking Branch
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	      // Enables ImGui to split and make it's own viewports	
		
		io.ConfigViewportsNoAutoMerge = false;					  // Set to make all floating imgui windows always create their own viewport. Otherwise, they are merged into the main host viewports when overlapping it. May also set ImGuiViewportFlags_NoAutoMerge on individual viewport.
		io.ConfigViewportsNoTaskBarIcon = true;					  // Disable default OS task bar icon flag for secondary viewports. When a viewport doesn't want a task bar icon, ImGuiViewportFlags_NoTaskBarIcon will be set on it.
		io.ConfigViewportsNoDecoration = false;					  // Disable default OS window decoration flag for secondary viewports. When a viewport doesn't want window decorations, ImGuiViewportFlags_NoDecoration will be set on it. Enabling decoration can create subsequent issues at OS levels (e.g. minimum window size).

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(Application::GetApplication().GetWindow().GetGLFWwindow(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init();
	}

	void ImGuiLayer::OnDetach() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		Draw();
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		GLFWwindow* backup_current_context = Application::GetApplication().GetWindow().GetGLFWwindow();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	void ImGuiLayer::Draw() {

	}

	bool ImGuiLayer::CreateButton(const char* label)
	{
		return ImGui::Button(label);
	}

	void ImGuiLayer::CreateColorEditWidget(const char* label, float col[4])
	{
		ImGui::ColorEdit4(label, col);
	}


	void ImGuiLayer::OnEvent(Event& event) {
	
	}

}