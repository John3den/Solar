#pragma once

#include "Geometry.h"
#include "orbit.h"
#include "Texture.h"
class Skybox;

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Renderer.h"
#include "Skybox.h"

class Renderer;
class Scene
{
public:
	void Destroy();
	Scene(Renderer renderer);
	void CreateOrbits();
	void CreateGeometries();
	void InitializeModels();
	void UpdateTime();
	void GenerateTextures(Renderer renderer);
	std::vector<Geometry> geometries;
	std::vector<Texture> textures;
	std::vector<Texture> normalMaps;
	std::vector<VAO> vao;
	std::vector<VBO> vbo;
	std::vector<EBO> ebo;
	std::vector<Orbit> orbits;
	Skybox* skybox;
	Camera camera;
	float alpha=0;
	double prevFrame = 0;
	double currentFrame = 0;
	float deltaTime;
};