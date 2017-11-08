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
	Mesh m_mesh;
};

