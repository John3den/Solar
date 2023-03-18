#include "pch.h"
#include "framework.h"
#include "scene.h"

namespace Engine
{
	float BodyRadii[10] = { 1, 0.4f, 1.3f, 1.4f, 1.5f, 1.7f, 2.0f, 1.9f, 1.0f, 2.0f };
	enum { earth, moon, venus, mars, merucury, jupiter, saturn, uranus, neptune, sun };


	std::string names[] =
	{
		"earth" ,"moon","venus","mars", "mercury", "jupiter",  "saturn", "uranus", "neptune", "sun"
	};


	void Scene::UpdateTime()
	{
		currentFrame = glfwGetTime();
		deltaTime = (currentFrame - prevFrame) / 4;
		prevFrame = currentFrame;
		alpha += deltaTime * PI;
	}


	void Scene::GenerateTextures(Renderer renderer)
	{
		std::string texPath = "";
		for (int i = 0; i < 10; i++)
		{
			texPath = "Textures/" + names[i] + ".png";
			Texture temp = Texture(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
			temp.TexUnit(*renderer.GetLightShader(phongLighting), "tex0", 0);
			textures.push_back(temp);
			if (i < 9)
			{
				texPath = "NormalMaps/" + names[i] + ".png";
				if (i >= 6)
				{
					texPath = "NormalMaps/default.png";
				}
				Texture map = Texture(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
				map.TexUnit(*renderer.GetLightShader(phongLighting), "normal0", 1);
				normalMaps.push_back(map);
			}
		}
	}



	Scene::Scene(Renderer renderer) :
		camera(Camera(width, height, glm::vec3(0.0f, 4.0f, 25.0f), 45.0f, 0.1f, 1000.0f)),
		skybox(new Skybox(Texture(std::string("Textures/SkyXP.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE), renderer))
	{
		InitializeModels();
		GenerateTextures(renderer);

	}

	void Scene::CreateOrbits()
	{
		for (int i = 0; i < 10; i++)
		{
			float a, b, orbitingSpeed;
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
			orbits.push_back(Engine::Orbit(a, b, orbitingSpeed));
		}
	}

	void Scene::CreateGeometries()
	{
		for (int i = 0; i < 10; i++)
		{
			Geometry g = Geometry(BodyRadii[i]);
			geometries.push_back(g);
		}
	}

	void Scene::InitializeModels()
	{
		CreateOrbits();
		CreateGeometries();
		for (int i = 0; i < 10; i++)
		{
			VAO tempvao = VAO();
			tempvao.Bind();
			VBO tempvbo = VBO(geometries[i].vertices, sizeof(geometries[i].vertices));
			EBO tempebo = EBO(geometries[i].indices, sizeof(geometries[i].indices));
			tempvao.LinkAttrib(tempvbo, 0, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)0);
			tempvao.LinkAttrib(tempvbo, 1, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(3 * sizeof(float)));
			tempvao.LinkAttrib(tempvbo, 2, 2, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(6 * sizeof(float)));
			tempvao.LinkAttrib(tempvbo, 3, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(8 * sizeof(float)));
			tempvao.LinkAttrib(tempvbo, 4, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(11 * sizeof(float)));
			tempvao.LinkAttrib(tempvbo, 5, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(14 * sizeof(float)));
			tempvao.Unbind();
			tempvbo.Unbind();
			tempebo.Unbind();
			vao.push_back(tempvao);
			vbo.push_back(tempvbo);
			ebo.push_back(tempebo);
		}
	}

	void Scene::Destroy()
	{
		for (int i = 0; i < 10; i++)
		{
			vao[i].Delete();
			vbo[i].Delete();
			ebo[i].Delete();
			textures[i].Delete();
		}
		(*skybox).GetTexture().Delete();
	}

	void Scene::Update(GLFWwindow* window)
	{
		if (camera.IsCursorHidden())
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		UpdateTime();
		camera.Inputs(window);
		camera.updateMatrix();
	}
}