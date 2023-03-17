#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#define PI 3.1415f

const int GEOMETRY_RESOLUTION = 100;
const int VERTEX_SIZE = 17;

class Geometry
{
public:
	Geometry(float radius);
	GLfloat vertices[GEOMETRY_RESOLUTION * GEOMETRY_RESOLUTION * VERTEX_SIZE];
	GLuint indices[(2 * GEOMETRY_RESOLUTION * (GEOMETRY_RESOLUTION - 1)) * 3];

};

