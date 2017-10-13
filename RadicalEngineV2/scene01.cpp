#include "stdafx.h"
#include "scene01.h"
#include "renderer.h"
#include "glm/vec3.hpp"

namespace
{
	float positionData[] =
	{
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f,  0.8f, 0.0f,
		-0.8f, -0.8f, 0.0f,
	};

	float colorData[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
	};

	glm::vec3 vPositionData[] =
	{
		glm::vec3(-0.8f, -0.8f, 0.0f),
		glm::vec3(0.8f, -0.8f, 0.0f),
		glm::vec3(0.0f,  0.8f, 0.0f),
	};

	glm::vec3 vColorData[] =
	{
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
	};

	glm::vec3 vertexData[] =
	{
		glm::vec3(-0.8f, -0.8f, 0.0f),
		glm::vec3(1.0f,  0.0f, 0.0f),
		glm::vec3(0.8f, -0.8f, 0.0f),
		glm::vec3(0.0f,  1.0f, 0.0f),
		glm::vec3(0.0f,  0.8f, 0.0f),
		glm::vec3(0.0f,  0.0f, 1.0f),
		glm::vec3(-0.8f, -0.8f, 0.0f),
		glm::vec3(1.0f,  0.0f, 0.0f),
	};

	enum vboID
	{
		POSITION,
		COLOR,
		VERTEX
	};
}

Scene01::Scene01(Engine* engine)
	: Scene(engine)
{
}

Scene01::~Scene01()
{
}

bool Scene01::Initialize()
{
	GLuint program = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\basic.vs", "..\\Resources\\Shaders\\basic.fs");

	GLuint vboHandles[3];
	glGenBuffers(3, vboHandles);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

	
	glGenVertexArrays(1, &m_vaoHandle);
	glBindVertexArray(m_vaoHandle);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexBuffer(0, vboHandles[POSITION], 0, sizeof(glm::vec3));
	glBindVertexBuffer(1, vboHandles[COLOR], 0, sizeof(glm::vec3));

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);
	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);

	return true;
}

void Scene01::Update()
{
}

void Scene01::Render()
{
	glBindVertexArray(m_vaoHandle);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Scene01::Shutdown()
{
}
