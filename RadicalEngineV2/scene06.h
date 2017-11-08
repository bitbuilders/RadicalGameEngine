#pragma once
#include "scene.h"
#include "engine.h"
#include "material.h"
#include "shader.h"
#include "camera.h"

class Scene06 : public Scene
{
public:
	Scene06(Engine* engine);
	~Scene06();

	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	void UpdateCube();

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

	Shader m_shader;
	Material m_material;

	Camera* m_camera;
};

