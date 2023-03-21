#pragma once
#include "Texture.h"
#include "Renderer.h"
namespace Engine
{
	class Renderer;
	class Skybox
	{
	public:
		Skybox(const Texture& tex, const Renderer& renderer);

		unsigned int GetVAO() const;
		Texture GetTexture() const;

		void GenerateSkyboxBuffers();
		void GenerateCubeMapTexture();

	private:
		unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
		unsigned int cubemapTexture;
		Texture skytex;
	};
}