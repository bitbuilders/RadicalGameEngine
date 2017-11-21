#pragma once
#include "glm\vec3.hpp"

class Material
{
public:
	Material();
	~Material();

public:
	void SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shine);
	bool LoadTexture2D(const std::string& filename, GLuint activeTexture);
	void SetTextures();
	void AddTexture(GLuint texture, GLuint activeTexture);

	static GLuint CreateTexture(GLuint width, GLuint height);

	bool LoadTextureCube(const std::string & basename, const std::vector<std::string>& suffixes, const std::string & type, GLuint activeTexture);

public:
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	float m_shine;

	struct TextureInfo
	{
		GLenum type;
		GLuint activeTexture;
		GLuint texture;
	};

	std::vector<TextureInfo> m_textures;
};

