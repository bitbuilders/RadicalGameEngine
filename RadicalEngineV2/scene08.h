#pragma once
#include "scene.h"
#include "engine.h"
#include "material.h"
#include "shader.h"
#include "camera.h"

class Scene08 : public Scene
{
public:
	Scene08(Engine* engine);
	~Scene08();

	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	void MoveLight();

	void UpdateInput();

	void UpdateCube();

private:
	Shader m_shader;
	Material m_material;

	Camera* m_camera;

	float m_rotation;
	float m_rotationSpeed = 10.0f;

	GLuint m_numOfVertices;
	int m_numOfLights = 0;
	bool m_pointLightMode = true;
};

