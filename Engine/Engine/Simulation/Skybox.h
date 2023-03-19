#pragma once
#include "Texture.h"
#include "Renderer.h"
namespace Engine
{
	class Renderer;
	class Skybox
	{
	public:
		Skybox(Texture tex, Renderer renderer);
		Texture GetTexture();
		void GenerateSkyboxBuffers();
		void GenerateCubeMapTexture();
		unsigned int GetVAO();
	private:
		unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
		unsigned int cubemapTexture;
		Texture skytex;
	};
}