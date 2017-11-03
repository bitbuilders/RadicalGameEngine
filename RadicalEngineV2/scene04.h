#pragma once
#include "scene.h"
#include "engine.h"
#include "material.h"
#include "shader.h"
#include "camera.h"

class Scene04 : public Scene
{
public:
	Scene04(Engine* engine);
	~Scene04();

	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	void UpdateCube();

private:
	//struct object
	//{
	//	// id / handles
	//	GLuint shaderProgram;
	//	GLuint vaoHandle;

	//	// transforms
	//	GLint mxModelViewUniform;
	//	GLint mxMVPUniform;
	//	GLint mxNormalUniform;

	//	// material
	//	GLint ambientMaterialUniform;
	//	GLint diffuseMaterialUniform;
	//	GLint specularMaterialUniform;

	//	// sampler
	//	GLint samplerUniform;
	//	GLint samplerUniform2;
	//};

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

	Shader m_shader;
	Material m_material;

	Camera* m_camera;
};

