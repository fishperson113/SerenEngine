#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui_internal.h>
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include<Core/Application.h>
#include "Core/Logger/Logger.h"
#include"Renderer/Renderer.h"
namespace SerenEngine {

	ImGuiLayer::ImGuiLayer()
		: Layer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		CORE_LOG_TRACE("ImGuiLayer::OnAttach");
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWPlatformWindow*>(app.GetWindow())->GetWindow();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	bool ImGuiLayer::OnWindowResizedEvent(const WindowResizedEvent& e) {
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

}