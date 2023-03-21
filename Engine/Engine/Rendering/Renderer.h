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

	const unsigned int width = 1920;
	const unsigned int height = 1080;
	class Scene;
	class Renderer
	{
	public:
		Renderer();
		void NewFrame();
		void RenderFrame(Scene scene);
		void Destroy();
		static GLFWwindow* Init();
		const std::shared_ptr<Shader> GetLightShader(LightingMode mode);
		void InitUI(GLFWwindow* window);
	private:
		int lightingType = 0;
		std::shared_ptr<Shader> phong;
		std::shared_ptr<Shader> simple;
		std::shared_ptr<Shader> lightSource;
		std::shared_ptr<Shader> skybox;

		void ActivateShader();
		void Clear();
		void RenderSkybox(Scene scene);
		void Frame(Scene scene);
		void RenderBodies(Scene scene);
		const std::shared_ptr<Shader> GetLightSourceShader();
		const std::shared_ptr<Shader> GetSkyboxShader();
	};
}