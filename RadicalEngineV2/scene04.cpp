#include "stdafx.h"
#include "Scene04.h"
#include "renderer.h"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "timer.h"
#include "image.h"
#include "input.h"
#include "light.h"
#include <iostream>

#define SPECULAR

float Input::s_scrollX = 0.0f;
float Input::s_scrollY = 0.0f;

namespace
{
	//float vertexData[] =
	//{
	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	//	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	//	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	//	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	//	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	//	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	//	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	//	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	//	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	//	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	//	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	//	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	//	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	//	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	//	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	//};

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

Scene04::Scene04(Engine* engine)
	: Scene(engine)
{
}

Scene04::~Scene04()
{
	delete m_camera;
}

bool Scene04::Initialize()
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

	//GLuint vboHandles[3];
	//glGenBuffers(3, vboHandles);
	GLuint vboHandle;
	glGenBuffers(1, &vboHandle);

	//glBindBuffer(GL_ARRAY_BUFFER, vboHandles[POSITION]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, vboHandles[COLOR]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vaoHandle);
	glBindVertexArray(m_vaoHandle);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	auto uvSize = sizeof(GLfloat) * 2;
	auto posNormSize = sizeof(glm::vec3) * 2;
	glBindVertexBuffer(0, vboHandle, 0, posNormSize + uvSize);
	glBindVertexBuffer(1, vboHandle, sizeof(glm::vec3), posNormSize + uvSize);
	glBindVertexBuffer(2, vboHandle, posNormSize, posNormSize + uvSize);

	//glBindVertexBuffer(0, vboHandles[POSITION], 0, sizeof(glm::vec3));
	//glBindVertexBuffer(1, vboHandles[COLOR], 0, sizeof(glm::vec3));
	//glBindVertexBuffer(1, vboHandle, 0, sizeof(glm::vec3));

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);
	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);
	glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(2, 2);

	//m_cube.mxModelViewUniform = glGetUniformLocation(m_shader.GetHandle(), "mxModelView");
	//m_cube.mxMVPUniform = glGetUniformLocation(m_shader.GetHandle(), "mxMVP");
	//m_cube.mxNormalUniform = glGetUniformLocation(m_shader.GetHandle(), "mxNormal");

	//m_cube.ambientMaterialUniform = glGetUniformLocation(m_shader.GetHandle(), "ambientMaterial");
	//m_cube.diffuseMaterialUniform = glGetUniformLocation(m_shader.GetHandle(), "diffuseMaterial");
	//m_cube.specularMaterialUniform = glGetUniformLocation(m_shader.GetHandle(), "specularMaterial");

	//m_cube.samplerUniform = glGetUniformLocation(m_shader.GetHandle(), "textureSampler");
	//m_cube.samplerUniform2 = glGetUniformLocation(m_shader.GetHandle(), "textureSampler2");

	//m_light.positionUniform = glGetUniformLocation(m_shader.GetHandle(), "lightPosition");
	//m_light.colorUniform = glGetUniformLocation(m_shader.GetHandle(), "lightColor");

	m_material.SetMaterial(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 0.3f, 0.6f), glm::vec3(1.0f, 1.0f, 1.0f), 16.0f);
	m_material.LoadTexture2D("../Resources/Textures/crate.bmp", GL_TEXTURE0 + 0);

	//m_cube.mxModelViewUniform = glGetUniformLocation(m_cube.shaderProgram, "mxModelView");
	//m_cube.mxMVPUniform = glGetUniformLocation(m_cube.shaderProgram, "mxMVP");
	//m_cube.mxNormalUniform = glGetUniformLocation(m_cube.shaderProgram, "mxNormal");

	//m_cube.ambientMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "ambientMaterial");
	//m_cube.diffuseMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "diffuseMaterial");
	//m_cube.specularMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "specularMaterial");

	//m_cube.samplerUniform = glGetUniformLocation(m_cube.shaderProgram, "textureSampler");
	//m_cube.samplerUniform2 = glGetUniformLocation(m_cube.shaderProgram, "textureSampler2");

	//m_light.positionUniform = glGetUniformLocation(m_cube.shaderProgram, "lightPosition");
	//m_light.colorUniform = glGetUniformLocation(m_cube.shaderProgram, "lightColor");

	//std::cout << m_cube.mxMVPUniform << std::endl;

	//int width;
	//int height;
	//int bpp;
	////const unsigned char* data = Image::LoadBMP("../Resources/Textures/crate.bmp", width, height, bpp);
	//stbi_uc* data = stbi_load("../Resources/Textures/crate.bmp", &width, &height, &bpp, 3);

	//glActiveTexture(GL_TEXTURE0 + 0);
	//glGenTextures(1, &m_textureImage);
	//glBindTexture(GL_TEXTURE_2D, m_textureImage);

	//int texStorageFormat = bpp == 4 ? GL_RGBA8 : GL_RGB8;
	//int texImageFormat = bpp == 4 ? GL_RGBA : GL_RGB;

	//glTexStorage2D(GL_TEXTURE_2D, 0, texStorageFormat, width, height);

	//glTexImage2D(GL_TEXTURE_2D, 0, texImageFormat, width, height, 0, texImageFormat, GL_UNSIGNED_BYTE, data);

	////glGenerateMipmap(GL_TEXTURE_2D);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glActiveTexture(GL_TEXTURE0 + 1);
	//glGenTextures(1, &m_textureImage2);
	//glBindTexture(GL_TEXTURE_2D, m_textureImage2);

	//int texStorageFormat2 = bpp2 == 4 ? GL_RGBA8 : GL_RGB8;
	//int texImageFormat2 = bpp2 == 4 ? GL_RGBA : GL_RGB;

	//glTexStorage2D(GL_TEXTURE_2D, 0, texStorageFormat2, width2, height2);

	//glTexImage2D(GL_TEXTURE_2D, 0, texImageFormat2, width2, height2, 0, texImageFormat2, GL_UNSIGNED_BYTE, data2);
	//if (bpp == 24)
	//{
	//	glTexStorage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height);

	//	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//	
	//	//glTextureStorage2D(m_textureLoc, 1, GL_RGB, width, height);

	//	//glTextureSubImage2D(m_textureLoc, 1, 0, 0, width, height, GL_RGB8, GL_UNSIGNED_BYTE, data);
	//}
	//else if (bpp == 32)
	//{
	//	glTexStorage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height);

	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//}

	//glBindSampler(m_textureImage, m_cube.samplerUniform);

	//glGenerateMipmap(GL_TEXTURE_2D);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	//delete data;
	//delete data2;

	m_camera = new Camera("camera", this);
	m_camera->Initialize(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f));

	Light* light = new Light("light", this);
	light->SetValues(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f));
	AddObject(light);

	m_engine->Get<Input>()->AddButton("escape click", Input::eButtonType::KEYBOARD, GLFW_KEY_ESCAPE);

	return true;
}

void Scene04::Update()
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

void Scene04::Render()
{
	glBindVertexArray(m_vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Scene04::Shutdown()
{
}

void Scene04::UpdateCube()
{
	Light* light = GetObject<Light>("light");

	// Ambient Color
	glm::vec3 ambientMaterial = glm::vec3(0.5f, 0.5f, 0.5f);
	//glUniform3fv(m_cube.ambientMaterialUniform, 1, &ambientMaterial[0]);
	m_shader.SetUniform("material.ambient", m_material.m_ambient);

	// Model Matrix
	//m_rotation += m_rotationSpeed * m_engine->Get<Timer>()->FrameTime();
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
