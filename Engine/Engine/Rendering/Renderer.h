#pragma once
#include <memory>
#include "ShaderClass.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "UI.h"
#include "Scene.h"
#include "FailedToCreateWindowException.h"
namespace Engine
{
	enum LightingMode { phongLighting, simpleLighting };

	class Scene;

	class Renderer
	{
	public:
		Renderer();

		const std::shared_ptr<Shader> GetLightShader(LightingMode mode) const;

		static GLFWwindow* Init();
		void NewFrame();
		void RenderFrame(const Scene& scene);
		void Destroy();
		void InitUI(GLFWwindow* window);
		
		static const unsigned int width = 1920;
		static const unsigned int height = 1080;
	private:
		std::shared_ptr<Shader> phong;
		std::shared_ptr<Shader> simple;
		std::shared_ptr<Shader> lightSource;
		std::shared_ptr<Shader> skybox;
		int lightingType = 0;

		void ActivateShader();
		void Clear();
		void RenderSkybox(const Scene& scene);
		void Frame(const Scene& scene);
		void RenderBodies(const Scene& scene);
		const std::shared_ptr<Shader> GetLightSourceShader();
		const std::shared_ptr<Shader> GetSkyboxShader();
	};
}