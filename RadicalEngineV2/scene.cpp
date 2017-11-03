#include "stdafx.h"
#include "scene.h"

Scene::~Scene()
{
	for (auto object : m_objects)
	{
		delete object;
	}
}
