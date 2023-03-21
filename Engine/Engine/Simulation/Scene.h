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

	class Camera;

	class Scene
	{
	public:
		Scene(const Renderer& renderer);

		float GetTime() const;
		VAO GetVAO(int i) const;
		VBO GetVBO(int i) const;
		EBO GetEBO(int i) const;
		Orbit GetOrbit(int i) const;
		std::shared_ptr<Skybox> GetSkybox() const;
		Geometry GetGeometry(int i) const;
		Texture GetTexture(int i) const;
		Texture GetNormalMap(int i) const;
		std::shared_ptr<Camera> GetCamera() const;

		void Destroy();
		void Update(GLFWwindow* window);
		void CreateGeometries();
		void InitializeModels();
		void UpdateTime();
		void SetOrbits(std::vector<Orbit> orb);
		void GenerateTextures(const Renderer& renderer);

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