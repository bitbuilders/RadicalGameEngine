#include "stdafx.h"
#include "Scene02.h"
#include "glm\vec3.hpp"
#include "glm\mat4x4.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "renderer.h"
#include "input.h"
#include "timer.h"
#include <iostream>

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

Scene02::Scene02(Engine* engine)
	: Scene(engine)
{
}

Scene02::~Scene02()
{
}

bool Scene02::Initialize()
{
	m_shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\transform.vs", "..\\Resources\\Shaders\\basic.fs");

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

	m_engine->Get<Input>()->AddButton("click", Input::eButtonType::MOUSE, 0);
	m_engine->Get<Input>()->AddAnalog("x-axis", Input::eAnalogType::MOUSE_X, 0);
	m_engine->Get<Input>()->AddAnalog("y-axis", Input::eAnalogType::MOUSE_Y, 0);

	glfwSetInputMode(m_engine->Get<Renderer>()->m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); // Disable input

	m_mxUniform = glGetUniformLocation(m_shaderProgram, "modelMatrix");

	return true;
}

void Scene02::Update()
{
	UpdateCursor();
}

void Scene02::Render()
{
	glBindVertexArray(m_vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void Scene02::Shutdown()
{
}

void Scene02::UpdateCursor()
{
	Input::eButtonState state = m_engine->Get<Input>()->GetButton("click");

	float x = m_engine->Get<Input>()->GetAnalogAbsolute("x-axis");
	float y = m_engine->Get<Input>()->GetAnalogAbsolute("y-axis");
	// Multiply by 2.0f to make range 0-2 then subtract by 1.0f to make it -1.0-1.0 (clip space)
	m_x = (x / m_engine->Get<Renderer>()->m_width) * 2.0f - 1.0f;
	m_y = (y / m_engine->Get<Renderer>()->m_height) * 2.0f - 1.0f;

	m_cursorAngle += (m_engine->Get<Timer>()->FrameTime() * m_rotationSpeed);
	glm::mat4 mxRotate = glm::rotate(glm::mat4(1.0f), m_cursorAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 mxScale = glm::scale(glm::mat4(1.0f), glm::vec3(m_cursorSize));
	glm::mat4 mxTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(m_x, -m_y, 0.0f));
	glm::mat4 mxTransform = mxTranslate * (mxRotate * mxScale);
	glUniformMatrix4fv(m_mxUniform, 1, GL_FALSE, &mxTransform[0][0]);

	//std::cout << m_engine->Get<Timer>()->FrameTime() << std::endl;
}
