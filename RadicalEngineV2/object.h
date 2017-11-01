#pragma once
#include <string>
#include "transform.h"
#include "scene.h"

class Object
{
public:
	Object(std::string name, Scene* scene);
	~Object();

public:
	virtual void Update() = 0;

public:
	std::string m_name;
	Transform m_transform;

protected:
	Scene* m_scene;
};

