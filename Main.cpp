#include "Renderer.h"
#include "Scene.h"
#include "Simulation.h"

std::vector<Engine::Orbit> orbits;
int main()
{
	GLFWwindow* window = NULL;
	try
	{
		window = Engine::Renderer::Init();
	}
	catch(std::string errorMessage) { std::cout << errorMessage; }
	Engine::Renderer renderer;
	Engine::Scene scene(renderer);
	CreateOrbits();
	scene.SetOrbits(orbits);
	renderer.InitUI(window);
	while (!glfwWindowShouldClose(window))
	{
		renderer.NewFrame();
		scene.Update(window);
		renderer.RenderFrame(scene);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	scene.Destroy();
	renderer.Destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}