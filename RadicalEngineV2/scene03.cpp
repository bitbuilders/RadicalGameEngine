#include "stdafx.h"
#include "scene03.h"
#include "renderer.h"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "timer.h"
#include <iostream>

#define PHONG

namespace
{
	float vertexData[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	enum vboID
	{
		POSITION,
		COLOR,
		VERTEX
	};
}

Scene03::Scene03(Engine* engine)
	: Scene(engine)
{
}

Scene03::~Scene03()
{
}

bool Scene03::Initialize()
{
	#ifdef PHONG
	m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\phong.vs", "..\\Resources\\Shaders\\phong.fs");
	#else
	m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\vertexlight.vs", "..\\Resources\\Shaders\\basic.fs");
	#endif

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

	glBindVertexBuffer(0, vboHandle, 0, sizeof(glm::vec3) * 2);
	glBindVertexBuffer(1, vboHandle, sizeof(glm::vec3), sizeof(glm::vec3) * 2);

	//glBindVertexBuffer(0, vboHandles[POSITION], 0, sizeof(glm::vec3));
	//glBindVertexBuffer(1, vboHandles[COLOR], 0, sizeof(glm::vec3));
	//glBindVertexBuffer(1, vboHandle, 0, sizeof(glm::vec3));

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);
	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);
	
	m_cube.mxModelViewUniform = glGetUniformLocation(m_cube.shaderProgram, "mxModelView");
	m_cube.mxMVPUniform = glGetUniformLocation(m_cube.shaderProgram, "mxMVP");
	m_cube.mxNormalUniform = glGetUniformLocation(m_cube.shaderProgram, "mxNormal");

	m_cube.ambientMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "ambientMaterial");
	m_cube.diffuseMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "diffuseMaterial");
	m_cube.specularMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "specularMaterial");

	m_light.positionUniform = glGetUniformLocation(m_cube.shaderProgram, "lightPosition");
	m_light.colorUniform = glGetUniformLocation(m_cube.shaderProgram, "lightColor");
	//std::cout << m_cube.mxMVPUniform << std::endl;

	return true;
}

void Scene03::Update()
{
	UpdateCube();
}

void Scene03::Render()
{
	glBindVertexArray(m_vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Scene03::Shutdown()
{
}

void Scene03::UpdateCube()
{
	// Ambient Color
	glm::vec3 ambientMaterial = glm::vec3(0.0f, 0.1f, 0.2f);
	glUniform3fv(m_cube.ambientMaterialUniform, 1, &ambientMaterial[0]);

	// Model Matrix
	m_rotation += m_rotationSpeed * m_engine->Get<Timer>()->FrameTime();
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 mxModel = translate * rotate;

	glm::mat4 mxView = glm::lookAt(glm::vec3(0.0f, 1.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	float aspect = ((float)m_engine->Get<Renderer>()->m_width / (float)m_engine->Get<Renderer>()->m_height);
	glm::mat4 mxProjection = glm::perspective(90.0f, aspect, 0.1f, 1000.0f);

	glm::mat4 mxModelView = mxView * mxModel;
	glUniformMatrix4fv(m_cube.mxModelViewUniform, 1, GL_FALSE, &mxModelView[0][0]);

	glm::mat4 mvp = mxProjection * mxView * mxModel;
	glUniformMatrix4fv(m_cube.mxMVPUniform, 1, GL_FALSE, &mvp[0][0]);

	// Normals
	glm::mat3 mxNormal = glm::mat3(mxModelView);
	mxNormal = glm::inverse(mxNormal);
	mxNormal = glm::transpose(mxNormal);
	glUniformMatrix3fv(m_cube.mxNormalUniform, 1, GL_FALSE, &mxNormal[0][0]);

	// Light Position and Color
	glm::vec3 lightPosition = mxView * glm::vec4(0.0f, 0.0f, 5.0f, 1.0f);
	glUniformMatrix4fv(m_light.positionUniform, 1, GL_FALSE, &lightPosition[0]);

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glUniform3fv(m_light.colorUniform, 1, &lightColor[0]);

	// Diffuse Light
	glm::vec3 diffuseMaterial = glm::vec3(0.0f, 0.5f, 0.75f);
	glUniform3fv(m_cube.diffuseMaterialUniform, 1, &diffuseMaterial[0]);

	// Specular Light
	glm::vec3 specularMaterial = glm::vec3(1.0f, 1.0f, 1.0f);
	glUniform3fv(m_cube.specularMaterialUniform, 1, &specularMaterial[0]);
}
