#pragma once

#include <glm/glm.hpp>

class Orbit
{
private:
	// ellipse parameters
	float a = 1, b = 1;
	float orbitingSpeed = 1;
public:
	Orbit(float a, float b, float speed);
	glm::vec2 GetPosition(float angle);
};

