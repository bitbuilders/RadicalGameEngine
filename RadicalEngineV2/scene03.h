#pragma once
#include "scene.h"
#include "engine.h"

class Scene03 : public Scene
{
public:
	Scene03(Engine* engine);
	~Scene03();

	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	void UpdateCube();

private:
	struct object
	{
		// id / handles
		GLuint shaderProgram;
		GLuint vaoHandle;

		// transforms
		GLint mxModelViewUniform;
		GLint mxMVPUniform;
		GLint mxNormalUniform;

		// material
		GLint ambientMaterialUniform;
		GLint diffuseMaterialUniform;
		GLint specularMaterialUniform;
	};

	struct light
	{
		GLint positionUniform;
		GLint colorUniform;
	};

	object m_cube;
	light m_light;

	float m_rotation;
	float m_rotationSpeed = 35.0f;

	GLuint m_vaoHandle;
};

