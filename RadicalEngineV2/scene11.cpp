#include "stdafx.h"
#include "Scene11.h"
#include "renderer.h"
#include "glm/vec3.hpp"
#include "glm/vector_relational.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/random.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/color_space.hpp"
#include "timer.h"
#include "image.h"
#include "input.h"
#include "light.h"
#include "myMeshLoader.h"
#include "model.h"
#include <iostream>
#include <random>

#define SPECULAR

// These already set in Scene04
//float Input::s_scrollX = 0.0f;
//float Input::s_scrollY = 0.0f;

Scene11::Scene11(Engine* engine)
	: Scene(engine)
{
}

Scene11::~Scene11()
{
	delete m_camera;
}

bool Scene11::Initialize()
{
	m_engine->Get<Input>()->AddButton("escape click", Input::eButtonType::KEYBOARD, GLFW_KEY_ESCAPE);

	auto light = new Light("light", this);
	light->m_transform.m_position = glm::vec3(0.0f, 0.0f, 2.0f);
	light->m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light->m_specular = glm::vec3(1.0f);

	AddObject(light);

	auto model = new Model("model", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_normalmap.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_normalmap.fs", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();


	model->m_material.m_ambient = glm::vec3(0.0f, 0.3f, 0.4f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.5f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shine = 0.4f * 128.0f;

	model->m_material.LoadTexture2D("..\\Resources\\Textures\\ogre_diffuse.bmp", GL_TEXTURE0);
	model->m_material.LoadTexture2D("..\\Resources\\Textures\\ogre_normal.bmp", GL_TEXTURE1);
	
	model->m_shader.SetUniform("material.ambient", glm::vec3(0.3f));
	model->m_shader.SetUniform("material.diffuse", glm::vec3(0.5f));
	model->m_shader.SetUniform("material.specular", glm::vec3(0.5f));
	model->m_shader.SetUniform("material.shininess", 16.0f);
	model->m_shader.SetUniform("light.ambient", light->m_ambient);
	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);

	model->m_mesh.Load("..\\Resources\\Meshes\\ogre.obj", true);
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);
	model->m_mesh.BindVertexAttrib(3, Mesh::eVertexType::TANGENT);

	model->m_cameraID = "camera";

	AddObject(model);

	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	data.type = Camera::eType::EDITOR;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);

	m_rotation = 0.0f;

	return true;
}

void Scene11::Update()
{
	auto camera = GetObject<Camera>("camera");
	auto light = GetObject<Light>("light");

	float dt = m_engine->Get<Timer>()->FrameTime();

	glm::quat rotation = glm::angleAxis(dt, glm::vec3(0.0f, 1.0f, 0.0f));
	light->m_transform.m_position = rotation * light->m_transform.m_position;
	glm::vec4 position = camera->GetView() * glm::vec4(light->m_transform.m_position, 1.0f);

	auto models = GetObjects<Model>();
	for (auto model : models)
	{
		model->m_shader.Use();
		//model->m_shader.SetUniform("light.position", position);
		model->m_shader.SetUniform("lightPosition", position);
	}

	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}

	if (m_engine->Get<Input>()->GetButton("escape click") == Input::eButtonState::DOWN)
	{
		glfwSetWindowShouldClose(m_engine->Get<Renderer>()->m_window, GLFW_TRUE);
	}
}

void Scene11::Render()
{
	auto renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}
}

void Scene11::Shutdown()
{
}