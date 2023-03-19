#pragma once
#include "Geometry.h"
#include "Texture.h"
#include <memory>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Renderer.h"
#include "Skybox.h"
namespace Engine
{
	class Skybox;
	class Renderer;
	class Scene
	{
	public:
		float GetTime();
		void Destroy();
		void Update(GLFWwindow* window);
		Scene(Renderer renderer);
		void CreateGeometries();
		void InitializeModels();
		void UpdateTime();
		void SetOrbits(std::vector<Orbit> orb);
		void GenerateTextures(Renderer renderer);
		std::shared_ptr<Camera> GetCamera();
		VAO GetVAO(int i);
		VBO GetVBO(int i);
		EBO GetEBO(int i);
		Orbit GetOrbit(int i);
		std::shared_ptr<Skybox> GetSkybox();
		Geometry GetGeometry(int i);
		Texture GetTexture(int i);
		Texture GetNormalMap(int i);

	private:
		std::vector<Texture> normalMaps;
		std::vector<Texture> textures;
		std::vector<Geometry> geometries;
		std::vector<Orbit> orbits;
		std::vector<VAO> vao;
		std::vector<VBO> vbo;
		std::vector<EBO> ebo;
		std::shared_ptr<Skybox> skybox;
		std::shared_ptr<Camera> camera;
		float time = 0;
		double prevFrame = 0;
		double currentFrame = 0;
		float deltaTime;
	};
}