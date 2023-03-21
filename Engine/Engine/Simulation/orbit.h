#pragma once
#include <vector>
#include <glm/glm.hpp>
namespace Engine
{

	class Orbit
	{
	public:
		Orbit(float a, float b, float speed);

		glm::vec2 GetPosition(float angle);

		static std::vector<Orbit> CreateOrbits();

	private:
		// ellipse parameters
		float a = 1, b = 1;
		float orbitingSpeed = 1;

	};

}