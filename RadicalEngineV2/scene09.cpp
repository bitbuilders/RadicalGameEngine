#include "stdafx.h"
#include "Scene09.h"
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

Scene09::Scene09(Engine* engine)
	: Scene(engine)
{
}

Scene09::~Scene09()
{
	delete m_camera;
}

bool Scene09::Initialize()
{
	m_engine->Get<Input>()->AddButton("escape click", Input::eButtonType::KEYBOARD, GLFW_KEY_ESCAPE);

	//int width2;
	//int height2;
	//int bpp2;
	//stbi_uc* data2 = stbi_load("../Resources/Textures/led_strips_MonaLisa.bmp", &width2, &height2, &bpp2, 3);
	//const unsigned char* data2 = Image::LoadBMP("../Resources/Textures/led_strips_MonaLisa.bmp", width2, height2, bpp2);

	//#ifdef TEXTURED
	//	m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong.vs", GL_VERTEX_SHADER);
	//	m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong.fs", GL_FRAGMENT_SHADER);
	//	//m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\texturedphong.vs", "..\\Resources\\Shaders\\texturedphong.fs");
	//#elif defined(MULTI)
	//	m_shader.CompileShader("..\\Resources\\Shaders\\multi_texturedphong.vs", GL_VERTEX_SHADER);
	//	m_shader.CompileShader("..\\Resources\\Shaders\\multi_texturedphong.fs", GL_FRAGMENT_SHADER);
	//	m_material.LoadTexture2D("../Resources/Textures/led_strips_MonaLisa.bmp", GL_TEXTURE0 + 1);
	//	//m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\multi_texturedphong.vs", "..\\Resources\\Shaders\\multi_texturedphong.fs");
	//#elif defined(SPECULAR)
	//	m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_specular.vs", GL_VERTEX_SHADER);
	//	m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_specular.fs", GL_FRAGMENT_SHADER);
	//	m_material.LoadTexture2D("../Resources/Textures/crate_specular.bmp", GL_TEXTURE0 + 1);
	//	//m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\texturedphong_specular.vs", "..\\Resources\\Shaders\\texturedphong_specular.fs");
	//	//data2 = stbi_load("../Resources/Textures/crate_specular.bmp", &width2, &height2, &bpp2, 3);
	//	//data2 = Image::LoadBMP("../Resources/Textures/crate_specular.bmp", width2, height2, bpp2);
	//#elif defined(PHONG)
	//	m_shader.CompileShader("..\\Resources\\Shaders\\phong.vs", GL_VERTEX_SHADER);
	//	m_shader.CompileShader("..\\Resources\\Shaders\\phong.fs", GL_FRAGMENT_SHADER);
	//	//m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\phong.vs", "..\\Resources\\Shaders\\phong.fs");
	//#else
	//	m_shader.CompileShader("..\\Resources\\Shaders\\vertexlight.vs", GL_VERTEX_SHADER);
	//	m_shader.CompileShader("..\\Resources\\Shaders\\basic.fs", GL_FRAGMENT_SHADER);
	//	//m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\vertexlight.vs", "..\\Resources\\Shaders\\basic.fs");
	//#endif
	// light
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);

	Light* light = new Light("light", this);
	light->m_transform.m_position = glm::vec3(3.0, 2.0, 1.0);
	glm::vec3 color = glm::rgbColor(glm::vec3(glm::linearRand(0.0f, 360.0f), 1.0f, 0.8f));
	light->m_diffuse = color;
	light->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	light->m_ambient = glm::vec3(0.6f, 0.6f, 0.6f);
	AddObject(light);

	// model
	auto model = new Model("model", this);
	model->m_transform.m_scale = glm::vec3(-1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.0f);

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
	//model->m_material.LoadTexture2D("..\\Resources\\Textures\\crate.bmp", GL_TEXTURE0);
	//model->m_material.LoadTexture2D("..\\Resources\\Textures\\crate_specular.bmp", GL_TEXTURE1);

	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shine);

	model->m_shader.SetUniform("light.ambient", light->m_ambient);
	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);

	model->m_mesh.Load("..\\Resources\\Meshes\\suzanne.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	model->m_cameraID = "camera_rtt";

	AddObject(model);

	model = new Model("cube", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong.fs", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	GLuint texture = Material::CreateTexture(512, 512);
	model->m_material.AddTexture(texture, GL_TEXTURE0);

	model->m_mesh.Load("..\\Resources\\Meshes\\cube.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	//model->m_shader.SetUniform("fog.distanceMin", 3.0f);
	//model->m_shader.SetUniform("fog.distanceMax", 20.0f);
	//model->m_shader.SetUniform("fog.color", glm::vec3(0.5f));

	model->m_cameraID = "camera";

	AddObject(model);

	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	data.type = Camera::eType::ORBIT;
	camera->Initialize(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);

	camera = new Camera("camera_rtt", this);
	data.type = Camera::eType::LOOK_AT;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);

	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
		GL_TEXTURE_2D, texture, 0);

	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	assert(result == GL_FRAMEBUFFER_COMPLETE);

	m_rotation = 0.0f;

	return true;
}

void Scene09::Update()
{
	//auto objects = GetObjects<Object>();
	//for (auto object : objects)
	//{
	//	object->Update();
	//}

	//UpdateCube();
	////glActiveTexture(GL_TEXTURE0 + 0);
	////glBindTexture(GL_TEXTURE_2D, m_textureImage);
	//m_shader.SetUniform("textureSampler", 0);
	////glUniform1i(m_cube.samplerUniform, 0);

	////glActiveTexture(GL_TEXTURE0 + 1);
	////glBindTexture(GL_TEXTURE_2D, m_textureImage2);
	//m_shader.SetUniform("textureSpecularSampler", 1);
	////glUniform1i(m_cube.samplerUniform2, 1);
	//m_camera->Update();

	Model* model = GetObject<Model>("model");
	//Camera* camera = GetObject<Camera>("camera");
	Light* light = GetObject<Light>("light");

	m_rotation = m_rotation + 10.0f * m_engine->Get<Timer>()->FrameTime();
	glm::quat rotation = glm::angleAxis(m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	model->m_transform.m_rotation = rotation;

	Camera* camera = GetObject<Camera>("camera_rtt");
	glm::vec4 position = camera->GetView() * glm::vec4(light->m_transform.m_position, 1.0f);
	model->m_shader.Use();
	model->m_shader.SetUniform("light.position", position);

	camera = GetObject<Camera>("camera");
	position = camera->GetView() * glm::vec4(light->m_transform.m_position, 1.0f);

	model = GetObject<Model>("cube");
	model->m_shader.Use();
	model->m_shader.SetUniform("light.position", position);

	//glm::vec4 position = camera->GetView() *  glm::vec4(light->m_transform.m_position, 1.0f);
	//model->m_shader.Use();
	//model->m_shader.SetUniform("light.position", position);

	//auto models = GetObjects<Model>();
	//for (auto m : models)
	//{
	//	m->m_shader.Use();
	//	m->m_shader.SetUniform("light.position", position);
	//}

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

void Scene09::Render()
{
	//glBindVertexArray(m_vaoHandle);
	//glDrawArrays(GL_TRIANGLES, 0, m_numOfVertices);
	////glBindVertexArray(m_vaoHandle);
	////glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindVertexArray(0);
	glViewport(0, 0, 512, 512);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto renderable = GetObject<Renderable>("model");
	renderable->Render();

	glFlush();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, m_engine->Get<Renderer>()->m_width, m_engine->Get<Renderer>()->m_height);
	glClearColor(0.8f, 0.8f, 0.8f, 0.8f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderable = GetObject<Renderable>("cube");
	renderable->Render();
	renderable = GetObject<Renderable>("light");
	renderable->Render();

	//std::vector<Renderable*> renderables = GetObjects<Renderable>();
	//for (auto renderable : renderables)
	//{
	//	renderable->Render();
	//}
}

void Scene09::Shutdown()
{
}