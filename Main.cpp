#include "Renderer.h"
#include "Scene.h"


int main()
{
	GLFWwindow* window = NULL;
	try
	{
		window = Engine::Renderer::Init();
	}
	catch(const Engine::FailedToCreateWindowException& exception) 
	{
		std::cout << exception.what();
		return 0;
	}
	Engine::Renderer renderer;
	Engine::Scene scene(renderer);
	scene.SetOrbits(Engine::Orbit::CreateOrbits());
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