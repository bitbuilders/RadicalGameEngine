#include "stdafx.h"
#include "light.h"
#include "camera.h"
#include "scene07.h"


Light::Light(const std::string& name, Scene* scene)
	: Renderable(name, scene)
{
	m_mesh.Load("..\\Resources\\Meshes\\cube.obj");
	m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	m_transform.m_scale = glm::vec3(0.2f);

	m_shader.CompileShader("..\\Resources\\Shaders\\basic_color.vs", GL_VERTEX_SHADER);
	m_shader.CompileShader("..\\Resources\\Shaders\\basic.fs", GL_FRAGMENT_SHADER);
	//m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong.vs", GL_VERTEX_SHADER);
//#ifdef SPOTLIGHT
//	m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_spotlight.fs", GL_FRAGMENT_SHADER);
//#else
//	m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_directional.fs", GL_FRAGMENT_SHADER);
//#endif
	m_shader.Link();
	m_shader.Use();

	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);
}


Light::~Light()
{
}

void Light::Update()
{
	m_shader.Use();

	Camera* camera = m_scene->GetObject<Camera>("camera");
	glm::mat4 mxMVP = camera->GetProjection() * camera->GetView() * m_transform.GetMatrix44();
	m_shader.SetUniform("mxMVP", mxMVP);
	m_shader.SetUniform("color", m_diffuse);
}

void Light::Render()
{
	if (m_isActive)
	{
		m_shader.Use();
		m_mesh.Render();
	}
}

void Light::SetValues(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	m_transform.m_position = position;
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
}
