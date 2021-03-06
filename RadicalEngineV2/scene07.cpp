#include "stdafx.h"
#include "Scene07.h"
#include "renderer.h"
#include "glm/vec3.hpp"
#include "glm/vector_relational.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "timer.h"
#include "image.h"
#include "input.h"
#include "light.h"
#include "myMeshLoader.h"
#include "model.h"
//#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"
#include <iostream>

#define SPOTLIGHT

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

Scene07::Scene07(Engine* engine)
	: Scene(engine)
{
}

Scene07::~Scene07()
{
	delete m_camera;
}

bool Scene07::Initialize()
{
	m_engine->Get<Input>()->AddButton("escape click", Input::eButtonType::KEYBOARD, GLFW_KEY_ESCAPE);
	m_engine->Get<Input>()->AddButton("mode", Input::eButtonType::KEYBOARD, GLFW_KEY_SPACE);

	// light
	Light* light = new Light("light", this);
	light->m_transform.m_position = glm::vec3(-5.0f, 3.0f, 5.0f);
	light->m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	light->m_ambient = glm::vec3(0.4f, 0.4f, 0.4f);
	AddObject(light);

	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	data.type = Camera::eType::ORBIT;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);

	// model
	auto model = new Model("model", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.0f);

#ifdef SPOTLIGHT
	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_spotlight.fs", GL_FRAGMENT_SHADER);
#else
	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_directional.fs", GL_FRAGMENT_SHADER);
#endif

	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_fog.vs", GL_VERTEX_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(0.0f, 0.3f, 0.4f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.5f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shine = 12.0f;
	model->m_material.LoadTexture2D("..\\Resources\\Textures\\crate.bmp", GL_TEXTURE0);
	//model->m_material.LoadTexture2D("..\\Resources\\Textures\\crate_specular.bmp", GL_TEXTURE1);

	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shine);

	model->m_shader.SetUniform("light.ambient", light->m_ambient);
	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);

#ifdef SPOTLIGHT
	float cutoffAngle = 30.0f;
	float lightExponent = 4.0f;
	model->m_shader.SetUniform("light.cutoff", glm::radians(cutoffAngle));
	model->m_shader.SetUniform("light.exponent", lightExponent);
	glm::mat3 viewDirectionMatrix = glm::mat3(camera->GetView());
	glm::vec3 direction = viewDirectionMatrix * glm::vec4(glm::vec3(0.0f, -1.0f, 0.0f), 0.0f);
	model->m_shader.SetUniform("light.direction", direction);
#endif

	model->m_mesh.Load("..\\Resources\\Meshes\\suzanne.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	model->m_shader.SetUniform("fog.distanceMin", 3.0f);
	model->m_shader.SetUniform("fog.distanceMax", 20.0f);
	model->m_shader.SetUniform("fog.color", glm::vec3(0.5f));

	AddObject(model);

	// Model 2 (plane)
	model = new Model("plane", this);
	model->m_transform.m_scale = glm::vec3(10.0f);
	model->m_transform.m_position = glm::vec3(0.0f, -1.0f, 0.0f);

#ifdef SPOTLIGHT
	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_spotlight.fs", GL_FRAGMENT_SHADER);
#else
	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_directional.fs", GL_FRAGMENT_SHADER);
#endif

	model->m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_fog.vs", GL_VERTEX_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(0.0f, 0.4f, 0.3f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.75f, 0.5f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shine = 12.0f;
	model->m_material.LoadTexture2D("..\\Resources\\Textures\\crate.bmp", GL_TEXTURE0);
	//model->m_material.LoadTexture2D("..\\Resources\\Textures\\crate_specular.bmp", GL_TEXTURE1);

	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shine);

	model->m_shader.SetUniform("light.ambient", light->m_ambient);
	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);

#ifdef SPOTLIGHT
	model->m_shader.SetUniform("light.cutoff", glm::radians(cutoffAngle));
	model->m_shader.SetUniform("light.exponent", lightExponent);
	model->m_shader.SetUniform("light.direction", direction);
#endif // SPOTLIGHT

	model->m_mesh.Load("..\\Resources\\Meshes\\plane.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	model->m_shader.SetUniform("fog.distanceMin", 3.0f);
	model->m_shader.SetUniform("fog.distanceMax", 20.0f);
	model->m_shader.SetUniform("fog.color", glm::vec3(0.5f));

	AddObject(model);

	m_rotation = 0.0f;

	return true;
}

void Scene07::Update()
{
	if (m_engine->Get<Input>()->GetButton("escape click") == Input::eButtonState::DOWN)
	{
		glfwSetWindowShouldClose(m_engine->Get<Renderer>()->m_window, GLFW_TRUE);
	}

	if (m_engine->Get<Input>()->GetButton("mode") == Input::eButtonState::DOWN)
	{
		m_pointLightMode = !m_pointLightMode;
		std::cout << m_pointLightMode << std::endl;
	}

	Model* model = GetObject<Model>("model");
	Camera* camera = GetObject<Camera>("camera");
	Light* light = GetObject<Light>("light");

	float dt = m_engine->Get<Timer>()->FrameTime();
	m_rotation = m_rotation + 5.0f * dt;
	glm::quat rotation = glm::angleAxis(m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	//light->m_transform.m_position = rotation * glm::vec3(0.0f, 0.0f, 2.0f);
	light->m_transform.m_position = rotation * glm::vec3(0.0f, 2.0f, 1.5f);
	float w = (m_pointLightMode) ? 1.0f : 0.0f;
	glm::vec4 position = camera->GetView() * glm::vec4(light->m_transform.m_position, w);
	//model->m_shader.SetUniform("light.position", position);
	//model->m_shader.Use();

	auto models = GetObjects<Model>();
	for (auto model : models)
	{
		model->m_shader.Use();
		model->m_shader.SetUniform("light.position", position);
	}

	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}


}

void Scene07::Render()
{
	//glBindVertexArray(m_vaoHandle);
	//glDrawArrays(GL_TRIANGLES, 0, m_numOfVertices);
	////glBindVertexArray(m_vaoHandle);
	////glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindVertexArray(0);
	std::vector<Renderable*> renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}
}

void Scene07::Shutdown()
{
}

void Scene07::MoveLight()
{


}

void Scene07::UpdateInput()
{

}

void Scene07::UpdateCube()
{
	Light* light = GetObject<Light>("light");

	// Ambient Color
	glm::vec3 ambientMaterial = glm::vec3(0.5f, 0.5f, 0.5f);
	//glUniform3fv(m_cube.ambientMaterialUniform, 1, &ambientMaterial[0]);
	m_shader.SetUniform("material.ambient", m_material.m_ambient);

	// Model Matrix
	//m_rotation += m_rotationSpeed * m_engine->Get<Timer>()->FrameTime();
	//std::cout << m_engine->Get<Timer>()->FrameTime() << std::endl;
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 mxModel = translate * rotate;

	//glm::mat4 mxView = glm::lookAt(glm::vec3(0.0f, 1.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mxView = m_camera->GetView();

	float aspect = ((float)m_engine->Get<Renderer>()->m_width / (float)m_engine->Get<Renderer>()->m_height);
	//glm::mat4 mxProjection = glm::perspective(90.0f, aspect, 0.1f, 1000.0f);
	glm::mat4 mxProjection = m_camera->GetProjection();

	glm::mat4 mxModelView = mxView * mxModel;
	//glUniformMatrix4fv(m_cube.mxModelViewUniform, 1, GL_FALSE, &mxModelView[0][0]);
	m_shader.SetUniform("mxModelView", mxModelView);

	glm::mat4 mvp = mxProjection * mxView * mxModel;
	//glUniformMatrix4fv(m_cube.mxMVPUniform, 1, GL_FALSE, &mvp[0][0]);
	m_shader.SetUniform("mxMVP", mvp);

	// Normals
	glm::mat3 mxNormal = glm::mat3(mxModelView);
	mxNormal = glm::inverse(mxNormal);
	mxNormal = glm::transpose(mxNormal);
	//glUniformMatrix3fv(m_cube.mxNormalUniform, 1, GL_FALSE, &mxNormal[0][0]);
	m_shader.SetUniform("mxNormal", mxNormal);

	// Light Position and Color
	//glm::vec3 lightPosition = mxView * glm::vec4(0.0f, 0.0f, 5.0f, 1.0f);
	glm::vec3 lightPosition = mxView * glm::vec4(light->m_transform.m_position, 1.0f);
	//glUniformMatrix4fv(m_light.positionUniform, 1, GL_FALSE, &lightPosition[0]);
	//m_shader.SetUniform("lightPosition", lightPosition);
	m_shader.SetUniform("light.position", lightPosition);

	//glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	//glUniform3fv(m_light.colorUniform, 1, &lightColor[0]);
	//m_shader.SetUniform("lightColor", lightColor);
	m_shader.SetUniform("light.ambient", light->m_ambient);
	m_shader.SetUniform("light.diffuse", light->m_diffuse);
	m_shader.SetUniform("light.specular", light->m_specular);

	// Diffuse Light
	glm::vec3 diffuseMaterial = glm::vec3(0.0f, 0.5f, 0.75f);
	//glUniform3fv(m_cube.diffuseMaterialUniform, 1, &diffuseMaterial[0]);
	m_shader.SetUniform("material.diffuse", m_material.m_diffuse);

	// Specular Light
	glm::vec3 specularMaterial = glm::vec3(1.0f, 1.0f, 1.0f);
	//glUniform3fv(m_cube.specularMaterialUniform, 1, &specularMaterial[0]);
	m_shader.SetUniform("material.specular", m_material.m_specular);

	m_shader.SetUniform("material.shininess", m_material.m_shine);
}
