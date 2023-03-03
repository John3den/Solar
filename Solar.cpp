
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

const int N = 50;
const int K = 12;

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

GLfloat sunvertices[(K * N + 2) * 3];

GLuint sunindices[(2 * N * (K - 1) + 2 * N) * 3];




void GenerateSphere(GLfloat* vertices, GLuint* indices, float radius)
{
	for (int j = 0; j < K; j++)
		for (int i = 0; i < N; i++)
		{
			float x, y, z;
			z = radius*(sin(j * PI / K)) * sin(2 * PI * i / ((float)N));
			x = radius * (sin(j * PI / K)) * cos(2 * PI * i / ((float)N));
			y = radius * cos(j * PI / K);

			vertices[(N * j + i) * (11)] = x;
			vertices[(N * j + i) * (11) + 1] = y;
			vertices[(N * j + i) * (11) + 2] = z;

			vertices[(N * j + i) * (11) + 3] = x;
			vertices[(N * j + i) * (11) + 4] = y;
			vertices[(N * j + i) * (11) + 5] = z;

			vertices[(N * j + i) * (11) + 6] = x;
			vertices[(N * j + i) * (11) + 7] = y;

			vertices[(N * j + i) * (11) + 8] = x;
			vertices[(N * j + i) * (11) + 9] = y;
			vertices[(N * j + i) * (11) + 10] = z;
		}


	vertices[(K * N + 0) * 11 + 0] = 0;
	vertices[(K * N + 0) * 11 + 1] = radius * 1;
	vertices[(K * N + 0) * 11 + 2] = 0;
	vertices[(K * N + 0) * 11 + 3] = 0.5f;
	vertices[(K * N + 0) * 11 + 4] = 0.5f;
	vertices[(K * N + 0) * 11 + 5] = 1.0f;
	vertices[(K * N + 0) * 11 + 6] = 0.5f;
	vertices[(K * N + 0) * 11 + 7] = 0.0f;
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


	float sunradius = 3.0f;

	for (int j = 0; j < K; j++)
		for (int i = 0; i < N; i++)
		{
			float x, y, z;
			z = sunradius*(sin(j * PI / K)) * sin(2 * PI * i / ((float)N));
			x = sunradius * (sin(j * PI / K)) * cos(2 * PI * i / ((float)N));
			y = sunradius * cos(j * PI / K);

			sunvertices[(N * j + i) * (3)] = x;
			sunvertices[(N * j + i) * (3) + 1] = y;
			sunvertices[(N * j + i) * (3) + 2] = z;

		}


	sunvertices[(K * N + 0) * 3 + 0] = 0;
	sunvertices[(K * N + 0) * 3 + 1] = sunradius * 1;
	sunvertices[(K * N + 0) * 3 + 2] = 0;
	sunvertices[(K * N + 1) * 3 + 0] = 0;
	sunvertices[(K * N + 1) * 3 + 1] = -1* sunradius;
	sunvertices[(K * N + 1) * 3 + 2] = 0;




	for (int i = 0; i < N; i++)
	{
		sunindices[(2 * N * (K - 1) + i) * 3 + 0] = (K * N + 0);
		sunindices[(2 * N * (K - 1) + i) * 3 + 1] = i;
		sunindices[(2 * N * (K - 1) + i) * 3 + 2] = i + 1;
	}

	sunindices[(2 * N * (K - 1) + N - 1) * 3 + 2] = 0;

	for (int i = N; i < N * 2; i++)
	{
		sunindices[(2 * N * (K - 1) + i) * 3 + 0] = (K * N + 1);
		sunindices[(2 * N * (K - 1) + i) * 3 + 1] = (K - 2) * N + i;
		sunindices[(2 * N * (K - 1) + i) * 3 + 2] = (K - 2) * N + i + 1;
	}

	sunindices[(2 * N * (K - 1) + 2 * N - 1) * 3 + 2] = (K - 1) * N;



	for (int j = 0; j < K - 1; j++)
	{
		for (int k = 0; k < N; k++)
		{
			sunindices[(j * N + k) * 6 + 0] = (j * N) + k;
			sunindices[(j * N + k) * 6 + 1] = (j * N) + k + 1;
			sunindices[(j * N + k) * 6 + 2] = (j * N) + k + N;

			sunindices[(j * N + k) * 6 + 3] = (j * N) + k + 1;
			sunindices[(j * N + k) * 6 + 4] = (j * N) + k + N;
			sunindices[(j * N + k) * 6 + 5] = (j * N) + k + N + 1;
		}
		sunindices[(j * N + N - 1) * 6 + 3] = (j * N);
		sunindices[(j * N + N - 1) * 6 + 4] = (j * N) + N;
		sunindices[(j * N + N - 1) * 6 + 5] = (j * N) + N - 1;
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
	VAO lightVAO;
	lightVAO.Bind();
	VBO lightVBO(sunvertices, sizeof(sunvertices));
	EBO lightEBO(sunindices, sizeof(sunindices));
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();






	glm::vec4 lightColor = glm::vec4(1.0f, 0.8f, 0.5f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, -1.5f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 earthPos = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::mat4 earthModel = glm::mat4(1.0f);
	earthModel = glm::translate(earthModel, earthPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		




	std::string texPath = "Textures/earth.png";

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

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		
		shaderProgram.Activate();

		currentFrame = glfwGetTime();

		float deltaTime = (currentFrame - prevFrame)/4;
		float rads[8] = {10, 15, 20, 40, 60 , 70 , 90, 110};
		prevFrame = currentFrame;

		alpha += deltaTime * PI;
		float earthPosX = rads[3] * sin(alpha);
		float earthPosZ = rads[3] * cos(alpha);

		earthPos = glm::vec3(earthPosX, 0.0f, earthPosZ);
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);
		
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

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		mercurytex.Bind();
		mercuryVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(mercuryindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		earthPos = glm::vec3(rads[1] * sin(alpha * 3), 0.0f, rads[1] * cos(alpha * 3));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		venustex.Bind();
		venusVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(venusindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		earthPos = glm::vec3(rads[3] * sin(alpha * 1.5f), 0.0f, rads[3] * cos(alpha * 1.5f));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		marstex.Bind();
		marsVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(marsindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		earthPos = glm::vec3(rads[4] * sin(alpha * 0.9f), 0.0f, rads[4] * cos(alpha * 0.9f));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		jupitertex.Bind();
		jupiterVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(jupiterindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		earthPos = glm::vec3(rads[5] * sin(alpha * 0.75f), 0.0f, rads[5] * cos(alpha * 0.75f));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		saturntex.Bind();
		saturnVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(saturnindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		earthPos = glm::vec3(rads[6] * sin(alpha * 0.6f), 0.0f, rads[6] * cos(alpha * 0.6f));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		uranustex.Bind();
		uranusVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(uranusindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		earthPos = glm::vec3(rads[7] * sin(alpha * 0.4f), 0.0f, rads[7] * cos(alpha * 0.4f));
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		neptunetex.Bind();
		neptuneVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(neptuneindices) / sizeof(int), GL_UNSIGNED_INT, 0);




		earthPos = glm::vec3(earthPosX + 3 * sin(alpha * 2), 0.0f, cos(alpha * 2) * 3 + earthPosZ);
		earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, earthPos);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(earthModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		moontex.Bind();
		MoonVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(moonindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(sunindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	earthtex.Delete();
	moontex.Delete();
	shaderProgram.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}