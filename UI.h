#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Orbit.h"
#include "Renderer.h"
class UI
{
public:
	void InitUI(GLFWwindow* window)
	{
		const char* glsl_version = "#version 420";
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		io.FontGlobalScale = 2;

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	}
	void CreateUIFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void RenderUI(int& lightingType)
	{
		{
			static float f = 0.0f;
			static int counter = 0;
			static ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
			bool t = true;
			ImGui::Begin("Hello, world!", &t, flags);
			if (ImGui::Button("Change Lighting Mode", ImVec2(300, 100)))
			{
				lightingType = (lightingType + 1) % 2;
			}
			ImGui::Text(lightingType == 0 ? "Phong lighting" : "Simple lighting");
			ImGui::SetWindowPos(ImVec2(0, 880));
			ImGui::SetWindowSize(ImVec2(1920, 200));

			ImGui::End();
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void ClearUI()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

};