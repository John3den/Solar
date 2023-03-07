#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include<filesystem>
namespace fs = std::filesystem;
#define PI 3.1415f
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

const unsigned int width = 1920;
const unsigned int height = 1080;

const int N = 100;
const int K = 100;

class Orbit
{
public:
	float a=1, b=1;
	float orbitingSpeed=1;
	float GetOrbitX(float angle)
	{
		return a*sin(angle * orbitingSpeed);
	}
	float GetOrbitZ(float angle)
	{
		return b*cos(angle * orbitingSpeed);
	}
};

// 0 - earth; 1 - moon; 2 - venus; 3 - mars; 4 - mercury; 5 - jupiter; 6 - saturn; 7 - uranus; 8 - neptune; 9 - sun
GLfloat BodyVertices[10][K * N * 17];
GLuint BodyIndices[10][(2 * N * (K - 1)) * 3];
float BodyRadii[10] = { 1, 0.4f, 1.3f, 1.4f, 1.5f, 1.7f, 2.0f, 1.9f, 1.0f, 2.0f };



void GenerateSphere(GLfloat* vertices, GLuint* indices, float radius)
{
	for (int j = 0; j < K; j++)
		for (int i = 0; i < N; i++)
		{
			float x, y, z;
			float phi = 2 * PI * i / ((float)(N-1));
			float theta= j * PI / (K-1);

			x = radius * (sin(theta)) * cos(phi);
			y = radius * cos(theta);
			z = radius * (sin(theta)) * sin(phi);

			glm::vec3 pos(x, y, z);
			glm::vec3 normal = glm::normalize(pos);
			glm::vec2 texCoordinate(phi / (2.0f * PI), (PI - theta) / PI);
			// VERTEX POSITION
			vertices[(N * j + i) * (17)] = x;
			vertices[(N * j + i) * (17) + 1] = y;
			vertices[(N * j + i) * (17) + 2] = z;
			// raw color
			vertices[(N * j + i) * (17) + 3] = 0;
			vertices[(N * j + i) * (17) + 4] = 0;
			vertices[(N * j + i) * (17) + 5] = 0;
			//TEXTURE COORDINATES
			vertices[(N * j + i) * (17) + 6] = texCoordinate.x;
			vertices[(N * j + i) * (17) + 7] = texCoordinate.y;
			//NORMAL
			vertices[(N * j + i) * (17) + 8] = normal.x;
			vertices[(N * j + i) * (17) + 9] = normal.y;
			vertices[(N * j + i) * (17) + 10] = normal.z;
			//TANGENT
			vertices[(N * j + i) * (17) + 11] = -sin(theta)*cos(phi);
			vertices[(N * j + i) * (17) + 12] = 0;
			vertices[(N * j + i) * (17) + 13] = sin(theta)*cos(phi);
			//BITANGENT
			vertices[(N * j + i) * (17) + 14] = cos(theta)*cos(phi);
			vertices[(N * j + i) * (17) + 15] = -sin(theta);
			vertices[(N * j + i) * (17) + 16] = cos(theta)*sin(phi);
		}
	for (int j = 0; j < K - 1; j++)
	{
		for (int k = 0; k < N; k++)
		{
			indices[(j * N + k) * 6 + 0] = (j * N) + k;
			indices[(j * N + k) * 6 + 1] = (j * N) + k + 1;
			indices[(j * N + k) * 6 + 2] = (j * N) + k + N;

			indices[(j * N + k) * 6 + 3] = (j * N) + k + 1;
			indices[(j * N + k) * 6 + 4] = (j * N) + k + N;
			indices[(j * N + k) * 6 + 5] = (j * N) + k + N + 1;
		}
		indices[(j * N + N - 1) * 6 + 3] = (j * N);
		indices[(j * N + N - 1) * 6 + 4] = (j * N) + N;
		indices[(j * N + N - 1) * 6 + 5] = (j * N) + N - 1;
	}
}

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


	VAO vao[10];
	VBO vbo[10];
	EBO ebo[10];
	for (int i = 0; i < 10; i++)
	{
		vao[i] = VAO();
		vao[i].Bind();
		vbo[i] = VBO(BodyVertices[i], sizeof(BodyVertices[i]));
		ebo[i] = EBO(BodyIndices[i], sizeof(BodyIndices[i]));
		vao[i].LinkAttrib(vbo[i], 0, 3, GL_FLOAT, 17 * sizeof(float), (void*)0);
		vao[i].LinkAttrib(vbo[i], 1, 3, GL_FLOAT, 17 * sizeof(float), (void*)(3 * sizeof(float)));
		vao[i].LinkAttrib(vbo[i], 2, 2, GL_FLOAT, 17 * sizeof(float), (void*)(6 * sizeof(float)));
		vao[i].LinkAttrib(vbo[i], 3, 3, GL_FLOAT, 17 * sizeof(float), (void*)(8 * sizeof(float)));
		vao[i].LinkAttrib(vbo[i], 4, 3, GL_FLOAT, 17 * sizeof(float), (void*)(11 * sizeof(float)));
		vao[i].LinkAttrib(vbo[i], 5, 3, GL_FLOAT, 17 * sizeof(float), (void*)(14 * sizeof(float)));
		vao[i].Unbind();
		vbo[i].Unbind();
		ebo[i].Unbind();

	}


	Shader lightShader("shaders/light.vert", "shaders/light.frag");
	Shader skyboxShader("Shaders/skybox.vert", "Shaders/skybox.frag");


	glm::vec4 lightColor = glm::vec4(1.0f, 0.8f, 0.5f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 planetPosition = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::mat4 planetModel = glm::mat4(1.0f);
	planetModel = glm::translate(planetModel, planetPosition);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(planetModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(planetModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	simpleLighting.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(planetModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	skyboxShader.Activate();
	
	std::string names[] =
	{
		"earth" ,"moon","venus","mars", "mercury", "jupiter",  "saturn", "uranus", "neptune", "sun"
	};
	
	std::string texPath = "Textures/SkyXP.png";

	Texture skytex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	skytex.texUnit(shaderProgram, "skybox", 0);

	Texture* Textures;
	Textures = (Texture*)malloc(10 * sizeof(Texture));

	for (int i = 0; i < 10; i++)
	{
		texPath = "Textures/" + names[i] + ".png";
		Textures[i] = Texture(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		Textures[i].texUnit(shaderProgram, "tex0", 0);
	}

	Texture* normalMaps;
	normalMaps = (Texture*)malloc(9 * sizeof(Texture));


	for (int i = 0; i < 9; i++)
	{
		texPath = "NormalMaps/" + names[i] + ".png";
		if (i >= 6)
		{
			texPath = "NormalMaps/default.png";
		}
		normalMaps[i] = Texture(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		normalMaps[i].texUnit(shaderProgram, "normal0", 1);
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

	Orbit orbits[10];

	for (int i = 0; i < 9; i++)
	{
		orbits[i].a = 13.0f + (i*2+1)*5.0f*(i/3.0f + 2.0f*sin(i/7.0f))/10.0f;
		orbits[i].b = 10.0f + (i*2+1)*(3.0f)*(i*log10(i+1) + 1)/10.0f;
		orbits[i].orbitingSpeed = 0.5f*(1+sin(i/3.0f));
	}

	orbits[1].a = 3;
	orbits[1].b = 3;
	orbits[1].orbitingSpeed = 2.0f;

	orbits[9].a = 0;
	orbits[9].b = 0;
	orbits[9].orbitingSpeed = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(camera.cursorHidden)
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
				planetPosition = glm::vec3(orbits[i].GetOrbitX(alpha + i * PI / 9.0f), 0.0f, orbits[i].GetOrbitZ(alpha + i * PI / 9.0f));
			else
				planetPosition = glm::vec3(orbits[0].GetOrbitX(alpha ) + orbits[i].GetOrbitX(alpha ), 0.0f, orbits[0].GetOrbitZ(alpha) + orbits[i].GetOrbitZ(alpha));
			planetModel = glm::mat4(1.0f);
			planetModel = glm::translate(planetModel, planetPosition);

			glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(planetModel));
			glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), 0, 0, 0);
			camera.Matrix(shaderProgram, "camMatrix");
			glActiveTexture(GL_TEXTURE0 + 0);
			Textures[i].Bind();
			glActiveTexture(GL_TEXTURE0 + 1);
			normalMaps[i].Bind();
			vao[i].Bind();
			glDrawElements(GL_TRIANGLES, sizeof(BodyIndices[i]) / sizeof(int), GL_UNSIGNED_INT, 0);
		}
		//render Sun
		lightShader.Activate();

		planetPosition = glm::vec3(orbits[9].GetOrbitX(alpha), 0.0f, orbits[9].GetOrbitZ(alpha));
		planetModel = glm::mat4(1.0f);
		planetModel = glm::translate(planetModel, planetPosition);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(planetModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		glActiveTexture(GL_TEXTURE0 + 0);
		Textures[9].Bind();
		vao[9].Bind();
		glDrawElements(GL_TRIANGLES, sizeof(BodyIndices[9]) / sizeof(int), GL_UNSIGNED_INT, 0);

	




		//Skybox rendering
		glDepthFunc(GL_LEQUAL);
		skyboxShader.Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
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
		Textures[i].Delete();
	}
	skytex.Delete();
	shaderProgram.Delete();
	lightShader.Delete();
	simpleLighting.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}