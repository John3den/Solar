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
		time += deltaTime * PI;
	}

	void Scene::GenerateTextures(const Renderer& renderer)
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



	Scene::Scene(const Renderer& renderer) :
		camera(new Camera(glm::vec3(0.0f, 4.0f, 25.0f), 45.0f, 0.1f, 1000.0f)),
		skybox(new Skybox(Texture(std::string("Textures/SkyXP.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE), renderer))
	{
		InitializeModels();
		GenerateTextures(renderer);

	}

	void Scene::SetOrbits(std::vector<Orbit> orb)
	{
		orbits = orb;
	}

	void Scene::CreateGeometries()
	{
		for (int i = 0; i < 10; i++)
		{
			Geometry g = Geometry(BodyRadii[i]);
			geometries.push_back(g);
		}
	}
	float Scene::GetTime() const
	{
		return time;
	}
	void Scene::InitializeModels()
	{
		CreateGeometries();
		for (int i = 0; i < 10; i++)
		{
			VAO tempvao = VAO();
			tempvao.Bind();
			VBO tempvbo = VBO(geometries[i].vertices, sizeof(geometries[i].vertices));
			EBO tempebo = EBO(geometries[i].indices, sizeof(geometries[i].indices));
			GLsizeiptr stride = VERTEX_SIZE * sizeof(float);
			tempvao.LinkAttrib(tempvbo, 0, 3, GL_FLOAT, stride, (void*)0);
			tempvao.LinkAttrib(tempvbo, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
			tempvao.LinkAttrib(tempvbo, 2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float)));
			tempvao.LinkAttrib(tempvbo, 3, 3, GL_FLOAT, stride, (void*)(8 * sizeof(float)));
			tempvao.LinkAttrib(tempvbo, 4, 3, GL_FLOAT, stride, (void*)(11 * sizeof(float)));
			tempvao.LinkAttrib(tempvbo, 5, 3, GL_FLOAT, stride, (void*)(14 * sizeof(float)));
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
		if (camera->IsCursorHidden())
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		UpdateTime();
		camera->Inputs(window);
		camera->updateMatrix();
	}
	std::shared_ptr<Camera> Scene::GetCamera() const
	{
		return camera;
	}
	VAO Scene::GetVAO(int i) const
	{
		return vao[i];
	}
	VBO Scene::GetVBO(int i) const
	{
		return vbo[i];
	}
	EBO Scene::GetEBO(int i) const
	{
		return ebo[i];
	}
	std::shared_ptr<Skybox> Scene::GetSkybox() const
	{
		return skybox;
	}
	Orbit Scene::GetOrbit(int i) const
	{
		return orbits[i];
	}
	Geometry Scene::GetGeometry(int i) const
	{
		return geometries[i];
	}
	Texture Scene::GetTexture(int i) const
	{
		return textures[i];
	}
	Texture Scene::GetNormalMap(int i) const
	{
		return normalMaps[i];
	}
}