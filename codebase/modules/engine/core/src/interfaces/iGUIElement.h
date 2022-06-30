#pragma once

#include "cpch.h"
#include "cdefs.h"

#include "imgui/imgui.h"


class IGUIElement {
public:
	virtual void Update() = 0;
	inline void Show() { display = true; }
	inline void Hide() { display = false; }

protected:
	bool display;
};

class iWindowManager {
public:
	iWindowManager() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	}

	~iWindowManager() {
		ImGui::DestroyContext();
	}


	virtual void Update() {
		ImGui::NewFrame();
		ImGuiIO& io = ImGui::GetIO();


		bool show = true;
		ShowDockspace(&show);

		for (size_t i = 0; i < windows.size(); i++)
		{
			windows[i]->Update();
		}


		ImGui::ShowDemoWindow();
		
		ImGui::Render();
	}

	void AddWindow(IGUIElement* newWindow) {
		windows.push_back(newWindow);
	}

	void ShowDockspace(bool* pOpen) {
		static bool opt_fullscreen_persistent = true;
		bool opt_fullscreen = opt_fullscreen_persistent;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// add a menu to the main dockspace window and set it to no docking. it should not be allowed to dock with 
		// itself
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking; 
		if (opt_fullscreen) {
			ImGuiViewport* vp = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(vp->Pos);
			ImGui::SetNextWindowSize(vp->Size);
			ImGui::SetNextWindowViewport(vp->ID);


			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
			window_flags |= ImGuiWindowFlags_NoBackground;
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		
		ImGui::Begin("###DockSpace", pOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		ImGui::End();
	
	}



private:
	std::vector<IGUIElement*> windows;

};