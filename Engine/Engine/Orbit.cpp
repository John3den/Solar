
#include "pch.h"
#include "framework.h"
#include "orbit.h"
namespace Engine
{

	Orbit::Orbit(float a, float b, float speed) :
		a(__max(a, 0.0f)),
		b(__max(b, 0.0f)),
		orbitingSpeed(__max(speed, 0.0f)) {}

	glm::vec2 Orbit::GetPosition(float angle)
	{
		float x = a * sin(angle * orbitingSpeed);
		float y = b * cos(angle * orbitingSpeed);
		return glm::vec2(x, y);
	}
}