#include "stdafx.h"
#include "model.h"
#include "camera.h"
#include "scene.h"
#include "timer.h"

Model::Model(std::string name, Scene* scene)
	: Renderable(name, scene)
{
}


Model::~Model()
{
}

void Model::Update()
{
	m_shader.Use();

	Camera* camera = m_scene->GetObject<Camera>("camera");

	static float angle = 0;
	static float speed = 10.0f;
	angle += m_scene->m_engine->Get<Timer>()->FrameTime() * speed;
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 mxView = camera->GetView();
	//glm::mat4 mxTranslate = glm::translate(glm::mat4(1.0f), m_transform.m_position);
	//glm::mat4 mxRotate = glm::mat4_cast(m_transform.m_rotation);
	//glm::mat4 mxScale = glm::scale(glm::mat4(1.0f), m_transform.m_scale);
	glm::mat4 mxMV = mxView * m_transform.GetMatrix44();
	m_shader.SetUniform("mxModelView", mxMV);

	glm::mat4 mxMVP = camera->GetProjection()  * mxMV;
	m_shader.SetUniform("mxMVP", mxMVP);

	glm::mat3 mxNormal = glm::mat3(mxMV);
	mxNormal = glm::inverse(mxNormal);
	mxNormal = glm::transpose(mxNormal);
	m_shader.SetUniform("mxNormal", mxNormal);
}

void Model::Render()
{
	m_shader.Use();
	m_material.SetTextures();
	m_mesh.Render();
}
