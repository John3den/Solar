#include "pch.h"
#include "framework.h"
#include "Renderer.h"
namespace Engine
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	enum { earth, moon, venus, mars, merucury, jupiter, saturn, uranus, neptune, sun };
	void Renderer::RenderBodies(Scene scene)
	{
		for (int i = 0; i < 9; i++)
		{
			// moon orbits earth so position is calculated differently
			if (i != moon)
				position = glm::vec3(scene.GetOrbit(i).GetPosition(scene.GetTime()).x, 
									0.0f,
									scene.GetOrbit(i).GetPosition(scene.GetTime()).y);
			else
				position = glm::vec3(scene.GetOrbit(0).GetPosition(scene.GetTime()).x + scene.GetOrbit(1).GetPosition(scene.GetTime()).x, 
									0.0f,
									scene.GetOrbit(0).GetPosition(scene.GetTime()).y + scene.GetOrbit(1).GetPosition(scene.GetTime()).y);
			model = glm::mat4(1.0f);
			model = glm::translate(model, position);
			//bind textures, buffers, normal maps and make a drawcall
			glUniformMatrix4fv(glGetUniformLocation((*GetLightShader(phongLighting)).GetID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniform3f(glGetUniformLocation((*GetLightShader(phongLighting)).GetID(), "camPos"), scene.GetCamera()->GetPosition().x, scene.GetCamera()->GetPosition().y, scene.GetCamera()->GetPosition().z);
			glUniform3f(glGetUniformLocation((*GetLightShader(phongLighting)).GetID(), "lightPos"), 0, 0, 0);
			scene.GetCamera()->Matrix((*GetLightShader(phongLighting)), "camMatrix");
			glActiveTexture(GL_TEXTURE0 + 0);
			scene.GetTexture(i).Bind();
			glActiveTexture(GL_TEXTURE0 + 1);
			scene.GetNormalMap(i).Bind();
			scene.GetVAO(i).Bind();
			glDrawElements(GL_TRIANGLES, sizeof(scene.GetGeometry(i).indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}
		//render Sun
		(*GetLightSourceShader()).Activate();
		//sets position and rotation
		position = glm::vec3(scene.GetOrbit(sun).GetPosition(scene.GetTime()).x, 0.0f, scene.GetOrbit(sun).GetPosition(scene.GetTime()).y);
		model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::rotate(model, scene.GetTime(), glm::vec3(0, 1, 0));
		//binds buffers and makes a drawcall
		glUniformMatrix4fv(glGetUniformLocation((*GetLightShader(phongLighting)).GetID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(glGetUniformLocation((*GetLightShader(phongLighting)).GetID(), "camPos"), scene.GetCamera()->GetPosition().x, scene.GetCamera()->GetPosition().y, scene.GetCamera()->GetPosition().z);
		scene.GetCamera()->Matrix((*GetLightShader(phongLighting)), "camMatrix");
		glActiveTexture(GL_TEXTURE0 + 0);
		scene.GetTexture(sun).Bind();
		scene.GetVAO(sun).Bind();
		glDrawElements(GL_TRIANGLES, sizeof(scene.GetGeometry(sun).indices) / sizeof(int), GL_UNSIGNED_INT, 0);
	}

	void Renderer::Destroy()
	{
		UI::ClearUI();
		GetSkyboxShader()->Delete();
		GetLightSourceShader()->Delete();
		GetLightShader(simpleLighting)->Delete();
		GetLightShader(phongLighting)->Delete();
	}
	void Renderer::Clear()
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Renderer::ActivateShader()
	{

		switch (lightingType)
		{
		case 0:
			(*GetLightShader(phongLighting)).Activate();
			break;
		case 1:
			(*GetLightShader(simpleLighting)).Activate();
			break;
		default:
			(*GetLightShader(phongLighting)).Activate();
			break;
		}
	}

	void Renderer::RenderSkybox(Scene scene)
	{
		glDepthFunc(GL_LEQUAL);
		(*GetSkyboxShader()).Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::mat4(glm::mat3(glm::lookAt(scene.GetCamera()->GetPosition(), scene.GetCamera()->GetPosition() + scene.GetCamera()->GetOrientation(), scene.GetCamera()->GetDirectionUp())));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation((*GetSkyboxShader()).GetID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation((*GetSkyboxShader()).GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(scene.GetSkybox()->GetVAO());
		glActiveTexture(GL_TEXTURE0);
		scene.GetSkybox()->GetTexture().Bind();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
	}

	GLFWwindow* Renderer::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(width, height, "Solar", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			throw std::string("Failed to initialize renderer");
		}
		glfwMakeContextCurrent(window);
		gladLoadGL();
		glViewport(0, 0, width, height);
		return window;
	}

	Renderer::Renderer() :
		simple(new Shader("shaders/SimpleLighting.vert", "shaders/SimpleLighting.frag")),
		phong(new Shader("shaders/default.vert", "shaders/default.frag")),
		lightSource(new Shader("shaders/light.vert", "shaders/light.frag")),
		skybox(new Shader("Shaders/skybox.vert", "Shaders/skybox.frag"))
	{
		glm::vec4 lightColor = glm::vec4(1.0f, 0.8f, 0.5f, 1.0f);
		glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);

		glm::vec3 position = glm::vec3(0.0f, 0.0f, 10.0f);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);


		lightSource->Activate();
		glUniformMatrix4fv(glGetUniformLocation(phong->GetID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(phong->GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(phong->GetID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		phong->Activate();
		glUniformMatrix4fv(glGetUniformLocation(phong->GetID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(phong->GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(phong->GetID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		simple->Activate();
		glUniformMatrix4fv(glGetUniformLocation(phong->GetID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(phong->GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(phong->GetID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		skybox->Activate();
		glEnable(GL_DEPTH_TEST);
	}

	const std::shared_ptr<Shader> Renderer::GetLightShader(LightingMode mode)
	{
		if (mode == phongLighting)
		{
			return phong;
		}
		if (mode == simpleLighting)
		{
			return simple;
		}
	}

	const std::shared_ptr<Shader> Renderer::GetLightSourceShader()
	{
		return lightSource;
	}

	const std::shared_ptr<Shader> Renderer::GetSkyboxShader()
	{
		return skybox;
	}

	void Renderer::Frame(Scene scene)
	{
		RenderBodies(scene);
		RenderSkybox(scene);
		UI::RenderUI(lightingType);
	}
	void Renderer::RenderFrame(Scene scene)
	{
		ActivateShader();
		Frame(scene);
	}
	void Renderer::NewFrame()
	{
		Clear();
		UI::CreateUIFrame();
	}

	void Renderer::InitUI(GLFWwindow* window)
	{
		UI::Init(window);
	}

}

