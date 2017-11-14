#include "stdafx.h"
#include "engine.h"
#include "renderer.h"
#include "glm\vec3.hpp"
#include "scene.h"
#include "scene01.h"
#include "scene02.h"
#include "scene03.h"
#include "scene04.h"
#include "scene05.h"
#include "scene06.h"
#include "scene07.h"
#include "scene08.h"

int main()
{
	std::shared_ptr<Engine> engine(new Engine);
	if (!engine->Initialize())
	{
		engine->Shutdown();
		exit(EXIT_FAILURE);
	}

	std::shared_ptr<Scene> scene(new Scene08(engine.get()));
	bool success = false;
	success = scene->Initialize();
	if (!success)
	{
		scene->Shutdown();
		engine->Shutdown();
		exit(EXIT_FAILURE);
	}

	while (!glfwWindowShouldClose(engine->Get<Renderer>()->m_window))
	{
		engine->Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render code
		engine->Update();
		scene->Update();
		scene->Render();

		glfwSwapBuffers(engine->Get<Renderer>()->m_window);
	}

	scene->Shutdown();
	engine->Shutdown();

	return 0;
}


