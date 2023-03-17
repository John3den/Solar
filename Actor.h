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
#include "Scene.h"
#include "Geometry.h"

class Actor : public Geometry
{
public:
	Actor(float radius);
	VAO vao;
	VBO vbo;
	EBO ebo;
};