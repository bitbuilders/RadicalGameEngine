#pragma once
#include <vector>
#include "engine.h"

class Object;

class Scene
{
public:
	Scene(Engine* engine) : m_engine(engine) {}

	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;

protected:
	Engine* m_engine;
	std::vector<Object*> m_objects;
};

