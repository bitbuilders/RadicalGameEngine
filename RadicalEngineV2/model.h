#pragma once
#include "renderable.h"
#include "mesh.h"

class Model : public Renderable
{
public:
	Model(std::string name, Scene* scene);
	~Model();

public:
	void Update();
	void Render();

public:
	Shader m_shader;
	Mesh m_mesh;
	std::string m_cameraID;
};

