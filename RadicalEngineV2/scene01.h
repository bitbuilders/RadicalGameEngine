#pragma once
#include "scene.h"
#include "engine.h"

class Scene01 : public Scene
{
public:
	Scene01(Engine* engine);
	~Scene01();

	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

private:
	GLuint m_vaoHandle;
};

