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
enum LightingMode {phongLighting, simpleLighting};

const unsigned int width = 1920;
const unsigned int height = 1080;
class Scene;
class Renderer
{
public:
	void Destroy();
	void Clear();
	void Frame(Scene scene);
	UI GUI;
	Renderer();
	static GLFWwindow* Init();
	void RenderSkybox(Scene scene);
	const std::shared_ptr<Shader> GetLightShader(LightingMode mode);
	const std::shared_ptr<Shader> GetLightSourceShader();
	const std::shared_ptr<Shader> GetSkyboxShader();
	void RenderBodies(Scene scene);
	int lightingType = 0;
	void ActivateShader();
private:
	std::shared_ptr<Shader> phong;
	std::shared_ptr<Shader> simple;
	std::shared_ptr<Shader> lightSource;
	std::shared_ptr<Shader> skybox;
};