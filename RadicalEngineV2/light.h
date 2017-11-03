#pragma once
#include "object.h"

class Light : public Object
{
public:
	Light(const std::string& name, Scene* scene);
	~Light();

public:
	void Update();
	void SetValues(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

public:
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

