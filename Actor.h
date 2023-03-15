#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Geometry.h"
#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Orbit.h"
#include "Actor.h"
#include "Scene.h"

class Actor
{
public:
	Actor(int index, Shader& shaderProgram);
	VAO GetVAO();
	VBO GetVBO();
	EBO GetEBO();
	Texture GetTexture();
	Texture GetNormalMap();
private:
	VAO vao;
	VBO vbo;
	EBO ebo;
	Texture texture;
	Texture normalMap;
};