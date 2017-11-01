#pragma once

#include "glm\vec3.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtc\matrix_transform.hpp"

class Transform
{
public:
	Transform();
	~Transform();

public:
	glm::mat4 GetMatrix44();

public:
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::quat m_rotation;
};

