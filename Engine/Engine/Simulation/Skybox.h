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

		unsigned int GetVAO();
		Texture GetTexture();

		void GenerateSkyboxBuffers();
		void GenerateCubeMapTexture();

	private:
		unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
		unsigned int cubemapTexture;
		Texture skytex;
	};
}