#include "stdafx.h"
#include "transform.h"


Transform::Transform()
{
	m_position = glm::vec3(0.0f);
	m_scale = glm::vec3(1.0f);
	m_rotation = glm::quat(glm::vec3(0.0f));
}


Transform::~Transform()
{
}

glm::mat4 Transform::GetMatrix44()
{
	glm::mat4 mxTranslate = glm::translate(glm::mat4(1.0f), m_position);
	glm::mat4 mxRotate = glm::mat4_cast(m_rotation);
	glm::mat4 mxScale = glm::scale(glm::mat4(1.0f), m_scale);

	return mxTranslate * mxRotate * mxScale;
}
