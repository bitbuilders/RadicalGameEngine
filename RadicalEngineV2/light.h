#pragma once
#include "renderable.h"
#include "mesh.h"

class Light : public Renderable
{
public:
	Light(const std::string& name, Scene* scene);
	~Light();

public:
	void Update();
	void Render();
	void SetValues(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

public:
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	glm::vec3 m_startingPosition;
	bool m_isActive = true;

protected:
	Shader m_shader;
	Mesh m_mesh;

};

