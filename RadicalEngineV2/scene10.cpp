#include "stdafx.h"
#include "Scene10.h"
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
//#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"
#include <iostream>
#include <random>

#define SPECULAR

// These already set in Scene04
//float Input::s_scrollX = 0.0f;
//float Input::s_scrollY = 0.0f;

namespace
{

	float vertexData[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f

	};


	enum vboID
	{
		POSITION,
		COLOR,
		VERTEX
	};
}

Scene10::Scene10(Engine* engine)
	: Scene(engine)
{
}

Scene10::~Scene10()
{
	delete m_camera;
}

bool Scene10::Initialize()
{
	m_engine->Get<Input>()->AddButton("escape click", Input::eButtonType::KEYBOARD, GLFW_KEY_ESCAPE);

	// light
	//auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	//srand(seed);

	//Light* light = new Light("light", this);
	//light->m_transform.m_position = glm::vec3(3.0, 2.0, 1.0);
	//glm::vec3 color = glm::rgbColor(glm::vec3(glm::linearRand(0.0f, 360.0f), 1.0f, 0.8f));
	//light->m_diffuse = color;
	//light->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	//light->m_ambient = glm::vec3(0.6f, 0.6f, 0.6f);
	//AddObject(light);

	// model
	auto model = new Model("skybox", this);
	model->m_transform.m_scale = glm::vec3(20.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\reflection.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\reflection.fs", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	GLuint skyboxIndex = glGetSubroutineIndex(model->m_shader.GetHandle(), GL_VERTEX_SHADER, "skybox");
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &skyboxIndex);

	model->m_material.m_ambient = glm::vec3(0.0f, 0.3f, 0.4f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.5f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shine = 0.4f * 128.0f;

	std::vector<std::string> suffixes = { "_posx", "_negx", "_posy", "_negy", "_posz", "_negz" };
	model->m_material.LoadTextureCube("..\\Resources\\Textures\\cubemaps\\lancellotti", suffixes, "jpg", GL_TEXTURE0);

	//model->m_material.LoadTexture2D("..\\Resources\\Textures\\crate.bmp", GL_TEXTURE0);
	//model->m_material.LoadTexture2D("..\\Resources\\Textures\\crate_specular.bmp", GL_TEXTURE1);

	//model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	//model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	//model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	//model->m_shader.SetUniform("material.shininess", model->m_material.m_shine);

	//model->m_shader.SetUniform("light.ambient", light->m_ambient);
	//model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	//model->m_shader.SetUniform("light.specular", light->m_specular);

	model->m_mesh.Load("..\\Resources\\Meshes\\cube.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);

	model->m_cameraID = "camera";

	AddObject(model);

	model = new Model("model", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\reflection.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\reflection.fs", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	skyboxIndex = glGetSubroutineIndex(model->m_shader.GetHandle(), GL_VERTEX_SHADER, "reflection");
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &skyboxIndex);

	model->m_material.m_ambient = glm::vec3(0.0f, 0.3f, 0.4f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.5f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shine = 0.4f * 128.0f;

	model->m_mesh.Load("..\\Resources\\Meshes\\suzanne.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);

	model->m_cameraID = "camera";

	AddObject(model);

	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	data.type = Camera::eType::EDITOR;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);

	m_rotation = 0.0f;

	return true;
}

void Scene10::Update()
{
	auto camera = GetObject<Camera>("camera");

	float dt = m_engine->Get<Timer>()->FrameTime();

	auto model = GetObject<Model>("model");
	model->m_transform.m_rotation = glm::quat(glm::vec3(0.0, dt, 0.0f)) 
		* model->m_transform.m_rotation;

	auto models = GetObjects<Model>();
	for (auto model : models)
	{
		glm::mat4 mxModel = model->m_transform.GetMatrix44();
		model->m_shader.Use();
		model->m_shader.SetUniform("mxModel", mxModel);
		model->m_shader.SetUniform("cameraWorldPosition", camera->m_transform.m_position);
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

void Scene10::Render()
{
	auto renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}
}

void Scene10::Shutdown()
{
}