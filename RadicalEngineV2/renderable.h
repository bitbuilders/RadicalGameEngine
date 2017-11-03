#pragma once
#include "object.h"
#include "shader.h"
#include "material.h"


class Renderable : public Object
{
public:
	Renderable(const std::string& name, Scene* scene);
	~Renderable();

public:
	void Update();
	void Render();

protected:
	Shader m_shader;
	Material m_material;
};

