#pragma once
#include "Texture.h"
#include "Renderer.h"
class Renderer;
class Skybox
{
public:
	Skybox(Texture tex, Renderer renderer);
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	Texture GetTexture();
	void GenerateSkyboxBuffers();
	void GenerateCubeMapTexture();
	unsigned int cubemapTexture;
private:
	Texture skytex;
};