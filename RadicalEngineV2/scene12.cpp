#include "stdafx.h"
#include "Scene12.h"
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
#define SHADOW_BUFFER_WIDTH	1024
#define SHADOW_BUFFER_HEIGHT 1024

// These already set in Scene04
//float Input::s_scrollX = 0.0f;
//float Input::s_scrollY = 0.0f;

Scene12::Scene12(Engine* engine)
	: Scene(engine)
{
}

Scene12::~Scene12()
{
	delete m_camera;
}

bool Scene12::Initialize()
{
	m_engine->Get<Input>()->AddButton("escape click", Input::eButtonType::KEYBOARD, GLFW_KEY_ESCAPE);
	
	m_depthShader = new Shader();
	m_depthShader->CompileShader("..\\Resources\\Shaders\\shadow_depth.vs", GL_VERTEX_SHADER);
	m_depthShader->CompileShader("..\\Resources\\Shaders\\shadow_depth.fs", GL_FRAGMENT_SHADER);
	m_depthShader->Link();

	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	data.type = Camera::eType::EDITOR;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	
	AddObject(camera);


	auto light = new Light("light", this);
	light->m_transform.m_position = glm::vec3(2.0f, 2.0f, 3.0f);
	light->m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light->m_specular = glm::vec3(1.0f);

	AddObject(light);

	auto model = new Model("model", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.25f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\phong.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\phong.fs", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(0.0f, 0.3f, 0.4f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.5f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shine = 0.4f * 128.0f;

	model->m_material.LoadTexture2D("..\\Resources\\Textures\\rocks.jpg", GL_TEXTURE0);
	//model->m_material.LoadTexture2D("..\\Resources\\Textures\\ogre_diffuse.bmp", GL_TEXTURE1);

	model->m_shader.SetUniform("material.ambient", glm::vec3(0.0f, 0.1f, 0.1f));
	model->m_shader.SetUniform("material.diffuse", glm::vec3(0.0f, 0.4f, 0.6f));
	model->m_shader.SetUniform("material.specular", glm::vec3(1.0f));
	model->m_shader.SetUniform("material.shininess", 16.0f);
	model->m_shader.SetUniform("light.ambient", light->m_ambient);
	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);

	model->m_mesh.Load("..\\Resources\\Meshes\\suzanne.obj", true);
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);
	//model->m_mesh.BindVertexAttrib(3, Mesh::eVertexType::TANGENT);

	model->m_cameraID = "camera";

	AddObject(model);


	model = new Model("floor", this);
	model->m_transform.m_scale = glm::vec3(8.0f);
	model->m_transform.m_position = glm::vec3(0.0f, -1.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong.fs", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(0.0f, 0.3f, 0.4f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.5f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shine = 0.4f * 128.0f;

	model->m_material.LoadTexture2D("..\\Resources\\Textures\\brick.png", GL_TEXTURE0);

	model->m_shader.SetUniform("material.ambient", glm::vec3(0.3f));
	model->m_shader.SetUniform("material.diffuse", glm::vec3(0.5f));
	model->m_shader.SetUniform("material.specular", glm::vec3(0.5f));
	model->m_shader.SetUniform("material.shininess", 16.0f);
	model->m_shader.SetUniform("light.ambient", light->m_ambient);
	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);

	model->m_mesh.Load("..\\Resources\\Meshes\\plane.obj", true);
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	model->m_cameraID = "camera";

	AddObject(model);


	model = new Model("debug", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.25f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\shadow_depth_debug.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\shadow_depth_debug.fs", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(0.0f, 0.3f, 0.4f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.5f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shine = 0.4f * 128.0f;

	GLuint depthTexture = model->m_material.CreateDepthTexture(SHADOW_BUFFER_WIDTH, SHADOW_BUFFER_HEIGHT);
	m_depthBuffer = model->m_material.CreateDepthbuffer(depthTexture, SHADOW_BUFFER_WIDTH, SHADOW_BUFFER_HEIGHT);
	model->m_material.AddTexture(depthTexture, GL_TEXTURE0);
	//model->m_material.LoadTexture2D("..\\Resources\\Textures\\rocks.jpg", GL_TEXTURE0);
	//model->m_material.LoadTexture2D("..\\Resources\\Textures\\ogre_normal.bmp", GL_TEXTURE1);

	model->m_shader.SetUniform("material.ambient", glm::vec3(0.3f));
	model->m_shader.SetUniform("material.diffuse", glm::vec3(0.5f));
	model->m_shader.SetUniform("material.specular", glm::vec3(0.5f));
	model->m_shader.SetUniform("material.shininess", 16.0f);
	model->m_shader.SetUniform("light.ambient", light->m_ambient);
	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);

	model->m_mesh.Load("..\\Resources\\Meshes\\quad.obj", true);
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::TEXCOORD);

	model->m_cameraID = "camera";

	AddObject(model);

	m_rotation = 0.0f;

	return true;
}

void Scene12::Update()
{
	auto camera = GetObject<Camera>("camera");
	auto light = GetObject<Light>("light");

	float dt = m_engine->Get<Timer>()->FrameTime();

	glm::quat rotation = glm::angleAxis(dt, glm::vec3(0.0f, 1.0f, 0.0f));
	light->m_transform.m_position = rotation * light->m_transform.m_position;

	glm::mat4 mxLightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f); 
	glm::mat4 mxLightView = glm::lookAt(light->m_transform.m_position, 
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 mxVP = mxLightProjection * mxLightView;
	m_depthShader->Use();
	m_depthShader->SetUniform("mxLVP", mxVP);

	glm::vec4 position = camera->GetView() * glm::vec4(light->m_transform.m_position, 1.0f);

	auto models = GetObjects<Model>();
	for (auto model : models)
	{
		model->m_shader.Use();
		model->m_shader.SetUniform("light.position", position);
		//model->m_shader.SetUniform("lightPosition", position);
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

void Scene12::Render()
{
	glViewport(0, 0, SHADOW_BUFFER_WIDTH, SHADOW_BUFFER_HEIGHT);

	glBindFramebuffer(GL_FRAMEBUFFER, m_depthBuffer);

	glClear(GL_DEPTH_BUFFER_BIT);

	m_depthShader->Use();

	auto model = GetObject<Model>("model");
	m_depthShader->SetUniform("mxModel", model->m_transform.GetMatrix44());
	model->m_mesh.Render();

	model = GetObject<Model>("floor");
	m_depthShader->SetUniform("mxModel", model->m_transform.GetMatrix44());
	model->m_mesh.Render();

	glFlush();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, m_engine->Get<Renderer>()->m_width, m_engine->Get<Renderer>()->m_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model = GetObject<Model>("debug");
	model->Render();

	auto renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}
}

void Scene12::Shutdown()
{
}