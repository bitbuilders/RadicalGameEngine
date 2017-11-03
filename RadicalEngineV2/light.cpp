#include "stdafx.h"
#include "light.h"


Light::Light(const std::string& name, Scene* scene)
	: Object(name, scene)
{
	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);
}


Light::~Light()
{
}

void Light::Update()
{
}

void Light::SetValues(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	m_transform.m_position = position;
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
}
