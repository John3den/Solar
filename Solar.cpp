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

GLfloat spherevertices[(K*N + 2) * 11];

GLuint sphereindices[(2*N*(K-1) + 2 * N) * 3];

GLfloat moonvertices[(K * N + 2) * 11];
GLuint moonindices[(2 * N * (K - 1) + 2 * N) * 3];

GLfloat venusvertices[(K * N + 2) * 11];
GLuint venusindices[(2 * N * (K - 1) + 2 * N) * 3];

GLfloat marsvertices[(K * N + 2) * 11];
GLuint marsindices[(2 * N * (K - 1) + 2 * N) * 3];

GLfloat mercuryvertices[(K * N + 2) * 11];
GLuint mercuryindices[(2 * N * (K - 1) + 2 * N) * 3];

GLfloat jupitervertices[(K * N + 2) * 11];
GLuint jupiterindices[(2 * N * (K - 1) + 2 * N) * 3];

GLfloat saturnvertices[(K * N + 2) * 11];
GLuint saturnindices[(2 * N * (K - 1) + 2 * N) * 3];

GLfloat uranusvertices[(K * N + 2) * 11];
GLuint uranusindices[(2 * N * (K - 1) + 2 * N) * 3];

GLfloat neptunevertices[(K * N + 2) * 11];
GLuint neptuneindices[(2 * N * (K - 1) + 2 * N) * 3];

GLfloat sunvertices[(K * N + 2) * 11];
GLuint sunindices[(2 * N * (K - 1) + 2 * N) * 3];



void GenerateSphere(GLfloat* vertices, GLuint* indices, float radius)
{
	for (int j = 0; j < K; j++)
		for (int i = 0; i < N; i++)
		{
			float x, y, z;
			float phi = 2 * PI * i / ((float)(N-1));
			float theta= j * PI / (K-1);
			z = radius*(sin(theta)) * sin(phi);
			x = radius * (sin(theta)) * cos(phi);
			y = radius * cos(theta);
			glm::vec3 pos(x, y, z);
			glm::vec3 normal = glm::normalize(pos);
			glm::vec2 texCoordinate(phi / (2.0f * PI), (PI - theta) / PI);
			// VERTEX POSITION
			vertices[(N * j + i) * (11)] = x;
			vertices[(N * j + i) * (11) + 1] = y;
			vertices[(N * j + i) * (11) + 2] = z;
			// raw color
			vertices[(N * j + i) * (11) + 3] = 0;
			vertices[(N * j + i) * (11) + 4] = 0;
			vertices[(N * j + i) * (11) + 5] = 0;
			//TEXTURE COORDINATES
			vertices[(N * j + i) * (11) + 6] = texCoordinate.x;
			vertices[(N * j + i) * (11) + 7] = texCoordinate.y;
			//NORMAL
			vertices[(N * j + i) * (11) + 8] = normal.x;
			vertices[(N * j + i) * (11) + 9] = normal.y;
			vertices[(N * j + i) * (11) + 10] = normal.z;
		}


	vertices[(K * N + 0) * 11 + 0] = 0;
	vertices[(K * N + 0) * 11 + 1] = radius * 1;
	vertices[(K * N + 0) * 11 + 2] = 0;
	vertices[(K * N + 0) * 11 + 3] = 0.5f;
	vertices[(K * N + 0) * 11 + 4] = 0.5f;
	vertices[(K * N + 0) * 11 + 5] = 1.0f;

	vertices[(K * N + 0) * 11 + 6] = 0.5f;
	vertices[(K * N + 0) * 11 + 7] = 1.0f;

	vertices[(K * N + 0) * 11 + 8] = 1;
	vertices[(K * N + 0) * 11 + 9] = 0;
	vertices[(K * N + 0) * 11 + 10] = 1.0f;


	vertices[(K * N + 1) * 11 + 0] = 0;
	vertices[(K * N + 1) * 11 + 1] = -1*radius;
	vertices[(K * N + 1) * 11 + 2] = 0;
	vertices[(K * N + 1) * 11 + 3] = 0.5f;
	vertices[(K * N + 1) * 11 + 4] = 0.5f;
	vertices[(K * N + 1) * 11 + 5] = 1.0f;

	vertices[(K * N + 1) * 11 + 6] = 0.5f;
	vertices[(K * N + 1) * 11 + 7] = 0.0f;

	vertices[(K * N + 1) * 11 + 8] = 1;
	vertices[(K * N + 1) * 11 + 9] = 0;
	vertices[(K * N + 1) * 11 + 10] = 1.0f;



	for (int i = 0; i < N; i++)
	{
		indices[(2 * N * (K - 1) + i) * 3 + 0] = (K * N + 0);
		indices[(2 * N * (K - 1) + i) * 3 + 1] = i;
		indices[(2 * N * (K - 1) + i) * 3 + 2] = i + 1;
	}

	indices[(2 * N * (K - 1) + N - 1) * 3 + 2] = 0;

	for (int i = N; i < N * 2; i++)
	{
		indices[(2 * N * (K - 1) + i) * 3 + 0] = (K * N + 1);
		indices[(2 * N * (K - 1) + i) * 3 + 1] = (K - 2) * N + i;
		indices[(2 * N * (K - 1) + i) * 3 + 2] = (K - 2) * N + i + 1;
	}

	indices[(2 * N * (K - 1) + 2 * N - 1) * 3 + 2] = (K - 1) * N;



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
	GenerateSphere(spherevertices, sphereindices, 1.0f);
	GenerateSphere(moonvertices, moonindices,0.5f);
	GenerateSphere(mercuryvertices, mercuryindices, 0.3f);
	GenerateSphere(venusvertices, venusindices, 0.9f);
	GenerateSphere(marsvertices, marsindices, 0.8f);
	GenerateSphere(jupitervertices, jupiterindices, 3.3f);
	GenerateSphere(saturnvertices, saturnindices, 3.0f);
	GenerateSphere(uranusvertices, uranusindices, 2.5f);
	GenerateSphere(neptunevertices, neptuneindices, 2.0f);
	GenerateSphere(sunvertices, sunindices, 5.0f);



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
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(spherevertices, sizeof(spherevertices));
	EBO EBO1(sphereindices, sizeof(sphereindices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();




	VAO MoonVAO;
	MoonVAO.Bind();
	VBO MoonVBO(moonvertices, sizeof(moonvertices));
	EBO MoonEBO(moonindices, sizeof(moonindices));
	MoonVAO.LinkAttrib(MoonVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	MoonVAO.LinkAttrib(MoonVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	MoonVAO.LinkAttrib(MoonVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	MoonVAO.LinkAttrib(MoonVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	MoonVAO.Unbind();
	MoonVBO.Unbind();
	MoonEBO.Unbind();

	VAO mercuryVAO;
	mercuryVAO.Bind();
	VBO mercuryVBO(mercuryvertices, sizeof(mercuryvertices));
	EBO mercuryEBO(mercuryindices, sizeof(mercuryindices));
	mercuryVAO.LinkAttrib(mercuryVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	mercuryVAO.LinkAttrib(mercuryVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	mercuryVAO.LinkAttrib(mercuryVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	mercuryVAO.LinkAttrib(mercuryVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	mercuryVAO.Unbind();
	mercuryVBO.Unbind();
	mercuryEBO.Unbind();

	VAO venusVAO;
	venusVAO.Bind();
	VBO venusVBO(venusvertices, sizeof(venusvertices));
	EBO venusEBO(venusindices, sizeof(venusindices));
	venusVAO.LinkAttrib(venusVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	venusVAO.LinkAttrib(venusVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	venusVAO.LinkAttrib(venusVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	venusVAO.LinkAttrib(venusVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	venusVAO.Unbind();
	venusVBO.Unbind();
	venusEBO.Unbind();


	VAO marsVAO;
	marsVAO.Bind();
	VBO marsVBO(marsvertices, sizeof(marsvertices));
	EBO marsEBO(marsindices, sizeof(marsindices));
	marsVAO.LinkAttrib(marsVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	marsVAO.LinkAttrib(marsVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	marsVAO.LinkAttrib(marsVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	marsVAO.LinkAttrib(marsVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	marsVAO.Unbind();
	marsVBO.Unbind();
	marsEBO.Unbind();

	VAO jupiterVAO;
	jupiterVAO.Bind();
	VBO jupiterVBO(jupitervertices, sizeof(jupitervertices));
	EBO jupiterEBO(jupiterindices, sizeof(jupiterindices));
	jupiterVAO.LinkAttrib(jupiterVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	jupiterVAO.LinkAttrib(jupiterVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	jupiterVAO.LinkAttrib(jupiterVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	jupiterVAO.LinkAttrib(jupiterVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	jupiterVAO.Unbind();
	jupiterVBO.Unbind();
	jupiterEBO.Unbind();

	VAO saturnVAO;
	saturnVAO.Bind();
	VBO saturnVBO(saturnvertices, sizeof(saturnvertices));
	EBO saturnEBO(saturnindices, sizeof(saturnindices));
	saturnVAO.LinkAttrib(saturnVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	saturnVAO.LinkAttrib(saturnVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	saturnVAO.LinkAttrib(saturnVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	saturnVAO.LinkAttrib(saturnVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	saturnVAO.Unbind();
	saturnVBO.Unbind();
	saturnEBO.Unbind();


	VAO uranusVAO;
	uranusVAO.Bind();
	VBO uranusVBO(uranusvertices, sizeof(uranusvertices));
	EBO uranusEBO(uranusindices, sizeof(uranusindices));
	uranusVAO.LinkAttrib(uranusVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	uranusVAO.LinkAttrib(uranusVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	uranusVAO.LinkAttrib(uranusVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	uranusVAO.LinkAttrib(uranusVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	uranusVAO.Unbind();
	uranusVBO.Unbind();
	uranusEBO.Unbind();

	VAO neptuneVAO;
	neptuneVAO.Bind();
	VBO neptuneVBO(neptunevertices, sizeof(neptunevertices));
	EBO neptuneEBO(neptuneindices, sizeof(neptuneindices));
	neptuneVAO.LinkAttrib(neptuneVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	neptuneVAO.LinkAttrib(neptuneVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	neptuneVAO.LinkAttrib(neptuneVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	neptuneVAO.LinkAttrib(neptuneVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	neptuneVAO.Unbind();
	neptuneVBO.Unbind();
	neptuneEBO.Unbind();



	Shader lightShader("shaders/light.vert", "shaders/light.frag");
	VAO sunVAO;
	sunVAO.Bind();
	VBO sunVBO(sunvertices, sizeof(sunvertices));
	EBO sunEBO(sunindices, sizeof(sunindices));
	sunVAO.LinkAttrib(sunVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	sunVAO.LinkAttrib(sunVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	sunVAO.LinkAttrib(sunVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	sunVAO.LinkAttrib(sunVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	sunVAO.Unbind();
	sunVAO.Unbind();
	sunVAO.Unbind();






	glm::vec4 lightColor = glm::vec4(1.0f, 0.8f, 0.5f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, -1.5f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 earthPos = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::mat4 earthModel = glm::mat4(1.0f);
	earthModel = glm::translate(earthModel, earthPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	simpleLighting.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Shader skyboxShader("Shaders/skybox.vert", "Shaders/skybox.frag");
	skyboxShader.Activate();
	



	std::string texPath = "Textures/sun.png";

	Texture suntex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	suntex.texUnit(shaderProgram, "tex0", 0);


	// debug


	texPath = "Textures/SkyXP.png";

	Texture skytex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	skytex.texUnit(shaderProgram, "skybox", 0);



	texPath = "Textures/earth.png";

	Texture earthtex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	earthtex.texUnit(shaderProgram, "tex0", 0);


	texPath = "Textures/moon.png";

	Texture moontex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	moontex.texUnit(shaderProgram, "tex0", 0);

	texPath = "Textures/venus.png";

	Texture venustex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	venustex.texUnit(shaderProgram, "tex0", 0);

	texPath = "Textures/mercury.png";

	Texture mercurytex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	mercurytex.texUnit(shaderProgram, "tex0", 0);

	texPath = "Textures/mars.png";

	Texture marstex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	marstex.texUnit(shaderProgram, "tex0", 0);

	texPath = "Textures/jupiter.png";

	Texture jupitertex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	jupitertex.texUnit(shaderProgram, "tex0", 0);

	texPath = "Textures/saturn.png";

	Texture saturntex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	saturntex.texUnit(shaderProgram, "tex0", 0);

	texPath = "Textures/uranus.png";

	Texture uranustex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	uranustex.texUnit(shaderProgram, "tex0", 0);

	texPath = "Textures/neptune.png";

	Texture neptunetex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	neptunetex.texUnit(shaderProgram, "tex0", 0);


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
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);







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
		//debug
		//deltaTime = 0;
		alpha += deltaTime * PI;
		float earthPosX = rads[2] * sin(alpha);	
		float earthPosZ = rads[2] * cos(alpha);

		earthPos = glm::vec3(earthPosX, 0.0f, earthPosZ);
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);
		earthModel = glm::rotate(earthModel, alpha*1.5f, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		earthtex.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(sphereindices) / sizeof(int), GL_UNSIGNED_INT, 0);


		

		earthPos = glm::vec3(earthPosX + 3*sin(alpha*2), 0.0f, cos(alpha*2)*3 + earthPosZ);
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		moontex.Bind();
		MoonVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(moonindices) / sizeof(int), GL_UNSIGNED_INT, 0);


		
		earthPos = glm::vec3(rads[0]*sin(alpha*2), 0.0f, rads[0]*cos(alpha*2));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);
		earthModel = glm::rotate(earthModel, alpha, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		mercurytex.Bind();
		mercuryVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(mercuryindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		earthPos = glm::vec3(rads[1] * sin(alpha * 3), 0.0f, rads[1] * cos(alpha * 3));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);
		earthModel = glm::rotate(earthModel, alpha, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		venustex.Bind();
		venusVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(venusindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		earthPos = glm::vec3(rads[3] * sin(alpha * 1.5f), 0.0f, rads[3] * cos(alpha * 1.5f));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);
		earthModel = glm::rotate(earthModel, alpha, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		marstex.Bind();
		marsVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(marsindices) / sizeof(int), GL_UNSIGNED_INT, 0);


		earthPos = glm::vec3(rads[4] * sin(alpha * 0.9f), 0.0f, rads[4] * cos(alpha * 0.9f));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);
		earthModel = glm::rotate(earthModel, alpha, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(simpleLighting.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(simpleLighting.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(simpleLighting, "camMatrix");
		jupitertex.Bind();
		jupiterVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(jupiterindices) / sizeof(int), GL_UNSIGNED_INT, 0);


		earthPos = glm::vec3(rads[5] * sin(alpha * 0.75f), 0.0f, rads[5] * cos(alpha * 0.75f));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);
		earthModel = glm::rotate(earthModel, alpha, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		saturntex.Bind();
		saturnVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(saturnindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		earthPos = glm::vec3(rads[6] * sin(alpha * 0.6f), 0.0f, rads[6] * cos(alpha * 0.6f));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);
		earthModel = glm::rotate(earthModel, alpha, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		uranustex.Bind();
		uranusVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(uranusindices) / sizeof(int), GL_UNSIGNED_INT, 0);


		

		earthPos = glm::vec3(rads[7] * sin(alpha * 0.4f), 0.0f, rads[7] * cos(alpha * 0.4f));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);
		earthModel = glm::rotate(earthModel, alpha, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		neptunetex.Bind();
		neptuneVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(neptuneindices) / sizeof(int), GL_UNSIGNED_INT, 0);
		
		lightShader.Activate();

		earthPos = glm::vec3(0,0,0);
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);
		earthModel = glm::rotate(earthModel, alpha/4.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(lightShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(lightShader, "camMatrix");
		suntex.Bind();
		sunVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(sunindices) / sizeof(int), GL_UNSIGNED_INT, 0);







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
			ImGui::Begin("Hello, world!", &t, flags);                          // Create a window called "Hello, world!" and append into it.

			//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);

			//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Change Lighting Mode", ImVec2(300,100)))                     // Buttons return true when clicked (most widgets return true when edited/activated)
			{
				lightingType = (lightingType + 1) % 2;
			}
			//ImGui::SameLine();
			//ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	skytex.Delete();
	earthtex.Delete();
	moontex.Delete();
	shaderProgram.Delete();
	lightShader.Delete();
	simpleLighting.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}