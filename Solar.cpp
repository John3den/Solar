#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Orbit.h"
#include "Geometry.h"
#include "Renderer.h"
#include "Skybox.h"
#include "Scene.h"
#include "UI.h"
namespace fs = std::filesystem;


int main()
{
	GLFWwindow* window = NULL;
	try
	{
		window = Renderer::Init();
	}
	catch(std::string errorMessage) { std::cout << errorMessage; }
	Renderer renderer;
	Scene scene(renderer);
	glEnable(GL_DEPTH_TEST);
	renderer.GUI.InitUI(window);
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();
		if(scene.camera.IsCursorHidden())
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		renderer.GUI.CreateUIFrame();
		scene.camera.Inputs(window);
		scene.camera.updateMatrix();
		renderer.ActivateShader();	
		scene.UpdateTime();
		renderer.Frame(scene);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	scene.Destroy();
	renderer.Destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}