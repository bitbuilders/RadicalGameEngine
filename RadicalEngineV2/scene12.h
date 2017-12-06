#pragma once
#include "scene.h"
#include "engine.h"
#include "material.h"
#include "shader.h"
#include "camera.h"

class Scene12 : public Scene
{
public:
	Scene12(Engine* engine);
	~Scene12();

	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

private:
	struct light
	{
		GLint positionUniform;
		GLint colorUniform;
	};

	//object m_cube;
	light m_light;

	float m_rotation;
	float m_rotationSpeed = 10.0f;

	GLuint m_vaoHandle;
	GLuint m_numOfVertices;

	GLuint m_frameBuffer;

	Shader m_shader;
	Material m_material;

	Camera* m_camera;

	GLuint m_depthBuffer = 0;
	Shader* m_depthShader = nullptr;
};

