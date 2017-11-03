#pragma once
#include <vector>
#include "engine.h"
#include "object.h"

class Scene
{
public:
	Scene(Engine* engine) : m_engine(engine) {}
	~Scene();

	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;

public:
	void AddObject(Object* object) { m_objects.push_back(object); }
	template <typename T>
	T* GetObject(const std::string & name);
	template <typename T>
	std::vector<T*> GetObjects();

public:
	Engine* m_engine;

protected:
	std::vector<Object*> m_objects;
};

template <typename T>
inline T * Scene::GetObject(const std::string & name)
{
	T* object = nullptr;

	for (auto obj : m_objects)
	{
		if (obj->m_name == name)
		{
			object = dynamic_cast<T*>(obj);
			break;
		}
	}

	return object;
}

template<typename T>
inline std::vector<T*> Scene::GetObjects()
{
	std::vector<T*> objects;

	for (auto obj : m_objects)
	{
		if (dynamic_cast<T*>(obj) != nullptr)
		{
			objects.push_back(dynamic_cast<T*>(obj));
		}
	}

	return objects;
}
