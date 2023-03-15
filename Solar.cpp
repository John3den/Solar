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

#define PI 3.1415f

namespace fs = std::filesystem;

std::vector<VAO> vao;
std::vector<VBO> vbo;
std::vector<EBO> ebo;


const unsigned int width = 1920;
const unsigned int height = 1080;

enum {earth, moon, venus, mars, merucury, jupiter, saturn, uranus, neptune, sun};

GLfloat BodyVertices[10][GEOMETRY_RESOLUTION * GEOMETRY_RESOLUTION * 17];
GLuint BodyIndices[10][(2 * GEOMETRY_RESOLUTION * (GEOMETRY_RESOLUTION - 1)) * 3];
float BodyRadii[10] = { 1, 0.4f, 1.3f, 1.4f, 1.5f, 1.7f, 2.0f, 1.9f, 1.0f, 2.0f };

std::vector<Texture> textures;
std::vector<Texture> normalMaps;




float skyboxVertices[] =
{
	//   Coordinates
	-1.0f, -1.0f,  1.0f,//        7--------6
	 1.0f, -1.0f,  1.0f,//       /|       /|
	 1.0f, -1.0f, -1.0f,//      4--------5 |
	-1.0f, -1.0f, -1.0f,//      | |      | |
	-1.0f,  1.0f,  1.0f,//      | 3------|-2
	 1.0f,  1.0f,  1.0f,//      |/       |/
	 1.0f,  1.0f, -1.0f,//      0--------1
	-1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};


void InitializeModels()
{
	for (int i = 0; i < 10; i++)
	{
		VAO tempvao = VAO();
		tempvao.Bind();
		VBO tempvbo = VBO(BodyVertices[i], sizeof(BodyVertices[i]));
		EBO tempebo = EBO(BodyIndices[i], sizeof(BodyIndices[i]));
		tempvao.LinkAttrib(tempvbo, 0, 3, GL_FLOAT, 17 * sizeof(float), (void*)0);
		tempvao.LinkAttrib(tempvbo, 1, 3, GL_FLOAT, 17 * sizeof(float), (void*)(3 * sizeof(float)));
		tempvao.LinkAttrib(tempvbo, 2, 2, GL_FLOAT, 17 * sizeof(float), (void*)(6 * sizeof(float)));
		tempvao.LinkAttrib(tempvbo, 3, 3, GL_FLOAT, 17 * sizeof(float), (void*)(8 * sizeof(float)));
		tempvao.LinkAttrib(tempvbo, 4, 3, GL_FLOAT, 17 * sizeof(float), (void*)(11 * sizeof(float)));
		tempvao.LinkAttrib(tempvbo, 5, 3, GL_FLOAT, 17 * sizeof(float), (void*)(14 * sizeof(float)));
		tempvao.Unbind();
		tempvbo.Unbind();
		tempebo.Unbind();
		vao.push_back(tempvao);
		vbo.push_back(tempvbo);
		ebo.push_back(tempebo);
	}
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		GenerateSphere(BodyVertices[i], BodyIndices[i], BodyRadii[i]);
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWwindow* window = glfwCreateWindow(width, height, "Solar", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, width, height);


	Shader simpleLighting("shaders/SimpleLighting.vert", "shaders/SimpleLighting.frag");
	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");
	Shader lightShader("shaders/light.vert", "shaders/light.frag");
	Shader skyboxShader("Shaders/skybox.vert", "Shaders/skybox.frag");

	InitializeModels();




	glm::vec4 lightColor = glm::vec4(1.0f, 0.8f, 0.5f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 planetPosition = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::mat4 planetModel = glm::mat4(1.0f);
	planetModel = glm::translate(planetModel, planetPosition);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(planetModel));
	glUniform4f(glGetUniformLocation(shaderProgram.GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.GetID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(planetModel));
	glUniform4f(glGetUniformLocation(shaderProgram.GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.GetID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	simpleLighting.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(planetModel));
	glUniform4f(glGetUniformLocation(shaderProgram.GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.GetID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	skyboxShader.Activate();
	
	std::string names[] =
	{
		"earth" ,"moon","venus","mars", "mercury", "jupiter",  "saturn", "uranus", "neptune", "sun"
	};
	
	std::string texPath = "Textures/SkyXP.png";

	Texture skytex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	skytex.TexUnit(shaderProgram, "skybox", 0);


	for (int i = 0; i < 10; i++)
	{
		texPath = "Textures/" + names[i] + ".png";
		Texture temp = Texture(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		temp.TexUnit(shaderProgram, "tex0", 0);
		textures.push_back(temp);
		if (i < 9)
		{
			texPath = "NormalMaps/" + names[i] + ".png";
			if (i >= 6)
			{
				texPath = "NormalMaps/default.png";
			}
			Texture map = Texture(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
			map.TexUnit(shaderProgram, "normal0", 1);
			normalMaps.push_back(map);
		}
	}


	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 4.0f, 25.0f));
	float alpha = 0;
	double prevFrame = glfwGetTime();
	double currentFrame = glfwGetTime();

	

	// Setup imgui
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

	int lightingType = 0;



	// Create VAO, VBO, and EBO for the skybox
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Creates the cubemap texture object
	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	std::vector<Orbit> orbits;

	for (int i = 0; i < 10; i++)
	{
		float a,b,orbitingSpeed;
		if (i == moon)
		{
			a = 3;
			b = 3;
			orbitingSpeed = 2.0f;
		}
		if (i == sun)
		{
			a = b = orbitingSpeed = 0;
		}
		else
		{
			a = 13.0f + (i * 2 + 1) * 5.0f * (i / 3.0f + 2.0f * sin(i / 7.0f)) / 10.0f;
			b = 10.0f + (i * 2 + 1) * (3.0f) * (i * log10(i + 1) + 1) / 10.0f;
			orbitingSpeed = 0.5f * (1 + sin(i / 3.0f));
		}
		orbits.push_back(Orbit(a, b, orbitingSpeed));
	}

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(camera.IsCursorHidden())
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		switch (lightingType)
		{
		case 0:
			shaderProgram.Activate();
			break;
		case 1:
			simpleLighting.Activate();
			break;
		default:
			shaderProgram.Activate();
			break;
		}
		

		currentFrame = glfwGetTime();

		float deltaTime = (currentFrame - prevFrame)/4;
		float rads[8] = {10, 15, 20, 40, 60 , 70 , 90, 110};
		prevFrame = currentFrame;
		alpha += deltaTime * PI;

		//Render planets
		for (int i = 0; i < 9; i++)
		{
			if (i != 1)
				planetPosition = glm::vec3(orbits[i].GetPosition(alpha + i * PI / 9.0f).x, 0.0f, orbits[i].GetPosition(alpha + i * PI / 9.0f).y);
			else
				planetPosition = glm::vec3(orbits[0].GetPosition(alpha ).x + orbits[i].GetPosition(alpha ).x, 0.0f, orbits[0].GetPosition(alpha).y + orbits[i].GetPosition(alpha).y);
			planetModel = glm::mat4(1.0f);
			planetModel = glm::translate(planetModel, planetPosition);

			glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(planetModel));
			glUniform3f(glGetUniformLocation(shaderProgram.GetID(), "camPos"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
			glUniform3f(glGetUniformLocation(shaderProgram.GetID(), "lightPos"), 0, 0, 0);
			camera.Matrix(shaderProgram, "camMatrix");
			glActiveTexture(GL_TEXTURE0 + 0);
			textures[i].Bind();
			glActiveTexture(GL_TEXTURE0 + 1);
			normalMaps[i].Bind();
			vao[i].Bind();
			glDrawElements(GL_TRIANGLES, sizeof(BodyIndices[i]) / sizeof(int), GL_UNSIGNED_INT, 0);
		}
		//render Sun
		lightShader.Activate();

		planetPosition = glm::vec3(orbits[sun].GetPosition(alpha).x, 0.0f, orbits[sun].GetPosition(alpha).y);
		planetModel = glm::mat4(1.0f);
		planetModel = glm::translate(planetModel, planetPosition);
		planetModel = glm::rotate(planetModel, alpha, glm::vec3(0, 1, 0));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(planetModel));
		glUniform3f(glGetUniformLocation(shaderProgram.GetID(), "camPos"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		camera.Matrix(shaderProgram, "camMatrix");
		glActiveTexture(GL_TEXTURE0 + 0);
		textures[sun].Bind();
		vao[sun].Bind();
		glDrawElements(GL_TRIANGLES, sizeof(BodyIndices[9]) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Skybox rendering
		glDepthFunc(GL_LEQUAL);
		skyboxShader.Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::mat4(glm::mat3(glm::lookAt(camera.GetPosition(), camera.GetPosition() + camera.GetOrientation(), camera.GetDirectionUp())));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.GetID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		skytex.Bind();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);

		//UI rendering
		{
			static float f = 0.0f;
			static int counter = 0;
			static ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
			bool t = true;
			ImGui::Begin("Hello, world!", &t, flags);                          
			if (ImGui::Button("Change Lighting Mode", ImVec2(300,100)))                     
			{
				lightingType = (lightingType + 1) % 2;
			}
			ImGui::Text(lightingType == 0 ? "Phong lighting" : "Simple lighting");
			ImGui::SetWindowPos(ImVec2(0,880));
			ImGui::SetWindowSize(ImVec2(1920, 200));
			
			ImGui::End();
		}


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	for (int i = 0; i < 10; i++)
	{
		vao[i].Delete();
		vbo[i].Delete();
		ebo[i].Delete();
		textures[i].Delete();
	}
	skytex.Delete();
	shaderProgram.Delete();
	lightShader.Delete();
	simpleLighting.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}