#pragma once
#include "scene.h"
#include "engine.h"

class Scene02 : public Scene
{
public:
	Scene02(Engine* engine);
	~Scene02();

	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	void UpdateCursor();

private:
	GLuint m_vaoHandle;
	GLuint m_shaderProgram;
	GLint m_mxUniform;
	float m_x;
	float m_y;
	float m_cursorSize = 0.1f;
	float m_rotationSpeed = 30.0f;
	float m_cursorAngle = 0.0f;
};

