#include "Simulation.h"

void CreateOrbits()
{
	for (int i = 0; i < 10; i++)
	{
		float a, b, orbitingSpeed;
		if (i == 1)
		{
			a = 2.1f;
			b = 1.9f;
			orbitingSpeed = 2.5f;
		}
		else if (i == 9)
		{
			a = b = orbitingSpeed = 0;
		}
		else
		{
			a = 13.0f + (i * 5+ 1) * 5.0f * (i / 3.0f + 2.0f * sin(i / 7.0f)) / 10.0f;
			b = 10.0f + (i * 5 + 1) * (3.0f) * (i * log10(i + 1) + 1) / 10.0f;
			orbitingSpeed = 0.2f * (1 + sin(i / 3.0f));
		}
		orbits.push_back(Engine::Orbit(a, b, orbitingSpeed));
	}
}