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
	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	Shader m_shader;
	Material m_material;
};

