#include "stdafx.h"
#include "Scene05.h"
#include "renderer.h"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "timer.h"
#include "image.h"
#include "input.h"
#include "light.h"
#include "myMeshLoader.h"
//#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"
#include <iostream>

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

Scene05::Scene05(Engine* engine)
	: Scene(engine)
{
}

Scene05::~Scene05()
{
	delete m_camera;
}

bool Scene05::Initialize()
{
	//int width2;
	//int height2;
	//int bpp2;
	//stbi_uc* data2 = stbi_load("../Resources/Textures/led_strips_MonaLisa.bmp", &width2, &height2, &bpp2, 3);
	//const unsigned char* data2 = Image::LoadBMP("../Resources/Textures/led_strips_MonaLisa.bmp", width2, height2, bpp2);

#ifdef TEXTURED
	m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong.vs", GL_VERTEX_SHADER);
	m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong.fs", GL_FRAGMENT_SHADER);
	//m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\texturedphong.vs", "..\\Resources\\Shaders\\texturedphong.fs");
#elif defined(MULTI)
	m_shader.CompileShader("..\\Resources\\Shaders\\multi_texturedphong.vs", GL_VERTEX_SHADER);
	m_shader.CompileShader("..\\Resources\\Shaders\\multi_texturedphong.fs", GL_FRAGMENT_SHADER);
	m_material.LoadTexture2D("../Resources/Textures/led_strips_MonaLisa.bmp", GL_TEXTURE0 + 1);
	//m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\multi_texturedphong.vs", "..\\Resources\\Shaders\\multi_texturedphong.fs");
#elif defined(SPECULAR)
	m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_specular.vs", GL_VERTEX_SHADER);
	m_shader.CompileShader("..\\Resources\\Shaders\\texturedphong_specular.fs", GL_FRAGMENT_SHADER);
	m_material.LoadTexture2D("../Resources/Textures/crate_specular.bmp", GL_TEXTURE0 + 1);
	//m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\texturedphong_specular.vs", "..\\Resources\\Shaders\\texturedphong_specular.fs");
	//data2 = stbi_load("../Resources/Textures/crate_specular.bmp", &width2, &height2, &bpp2, 3);
	//data2 = Image::LoadBMP("../Resources/Textures/crate_specular.bmp", width2, height2, bpp2);
#elif defined(PHONG)
	m_shader.CompileShader("..\\Resources\\Shaders\\phong.vs", GL_VERTEX_SHADER);
	m_shader.CompileShader("..\\Resources\\Shaders\\phong.fs", GL_FRAGMENT_SHADER);
	//m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\phong.vs", "..\\Resources\\Shaders\\phong.fs");
#else
	m_shader.CompileShader("..\\Resources\\Shaders\\vertexlight.vs", GL_VERTEX_SHADER);
	m_shader.CompileShader("..\\Resources\\Shaders\\basic.fs", GL_FRAGMENT_SHADER);
	//m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\vertexlight.vs", "..\\Resources\\Shaders\\basic.fs");
#endif
	m_shader.Link();
	m_shader.Use();

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	MyMeshLoader::LoadMesh("..\\Resources\\Meshes\\bunny.obj", vertices, normals, uvs);

	m_numOfVertices = vertices.size();
	//m_numOfVertices = vertices.size();

	GLuint vboHandle[3];
	glGenBuffers(3, vboHandle);

	//glBindBuffer(GL_ARRAY_BUFFER, vboHandles[POSITION]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, vboHandles[COLOR]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
	
	//int sizeOfIndividualData = sizeof(tinyobj::real_t);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
	if (vertices.size() > 0)
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
	if (normals.size() > 0)
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[2]);
	if (uvs.size() > 0)
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vaoHandle);
	glBindVertexArray(m_vaoHandle);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//auto uvSize = sizeof(GLfloat) * 2;
	//auto posNormSize = sizeof(glm::vec3) * 2;
	//glBindVertexBuffer(0, vboHandle, 0, posNormSize + uvSize);
	//glBindVertexBuffer(1, vboHandle, sizeof(glm::vec3), posNormSize + uvSize);
	//glBindVertexBuffer(2, vboHandle, posNormSize, posNormSize + uvSize);

	//auto uvSize = sizeof(tinyobj::real_t) * 2;
	//auto otherSize = sizeof(tinyobj::real_t) * 3;
	auto stride = sizeof(glm::vec3);
	auto uvStride = sizeof(glm::vec2);
	auto posNormSize = sizeof(glm::vec3) * 2;
	glBindVertexBuffer(0, vboHandle[0], 0, stride);
	if (normals.size() > 0)
		glBindVertexBuffer(1, vboHandle[1], 0, stride);
	if (uvs.size() > 0)
		glBindVertexBuffer(2, vboHandle[2], 0, uvStride);

	//glBindVertexBuffer(0, vboHandles[POSITION], 0, sizeof(glm::vec3));
	//glBindVertexBuffer(1, vboHandles[COLOR], 0, sizeof(glm::vec3));
	//glBindVertexBuffer(1, vboHandle, 0, sizeof(glm::vec3));

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);
	if (normals.size() > 0)
	{
		glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(1, 1);
	}
	if (uvs.size() > 0)
	{
		glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(2, 2);
	}

	m_material.SetMaterial(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 0.3f, 0.6f), glm::vec3(1.0f, 1.0f, 1.0f), 16.0f);
	m_material.LoadTexture2D("../Resources/Textures/crate.bmp", GL_TEXTURE0 + 0);

	m_camera = new Camera("camera", this);
	m_camera->Initialize(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f));

	Light* light = new Light("light", this);
	light->SetValues(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f));
	AddObject(light);

	m_engine->Get<Input>()->AddButton("escape click", Input::eButtonType::KEYBOARD, GLFW_KEY_ESCAPE);

	return true;
}

void Scene05::Update()
{
	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}

	UpdateCube();
	//glActiveTexture(GL_TEXTURE0 + 0);
	//glBindTexture(GL_TEXTURE_2D, m_textureImage);
	m_shader.SetUniform("textureSampler", 0);
	//glUniform1i(m_cube.samplerUniform, 0);

	//glActiveTexture(GL_TEXTURE0 + 1);
	//glBindTexture(GL_TEXTURE_2D, m_textureImage2);
	m_shader.SetUniform("textureSpecularSampler", 1);
	//glUniform1i(m_cube.samplerUniform2, 1);
	m_camera->Update();

	if (m_engine->Get<Input>()->GetButton("escape click") == Input::eButtonState::DOWN)
	{
		glfwSetWindowShouldClose(m_engine->Get<Renderer>()->m_window, GLFW_TRUE);
	}
}

void Scene05::Render()
{
	glBindVertexArray(m_vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, m_numOfVertices);
	//glBindVertexArray(m_vaoHandle);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Scene05::Shutdown()
{
}

void Scene05::UpdateCube()
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
