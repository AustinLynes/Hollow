#include "window_manager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"

#include "imgui/imgui_impl_opengl3.h"

WindowManager::WindowManager()
{
	win = new Window("Some Name", 1280, 720, CENTER_SCREEN_X(1280), CENTER_SCREEN_Y(720), nullptr);

	ImGui_ImplGlfw_InitForOpenGL(win->GetWindowPointer(), true);
	const char* glsl_version = "#version 460";
	ImGui_ImplOpenGL3_Init(glsl_version);

}

WindowManager::~WindowManager()
{
	ImGui_ImplOpenGL3_Shutdown();

}

void WindowManager::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	iWindowManager::Update();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backup = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup);
	}

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	win->SwapBuffers();

}

