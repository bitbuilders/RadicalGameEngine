#include "stdafx.h"
#include "material.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Material::Material()
	: m_ambient(0.2f), m_diffuse(0.0f, 0.4f, 0.7f), m_specular(1.0f)
{
}


Material::~Material()
{
}

void Material::SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shine)
{
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
	m_shine = shine;
}

bool Material::LoadTexture2D(const std::string& filename, GLuint activeTexture)
{
	bool success = false;

	int width = 0;
	int height = 0;
	int n = 0;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &n, 0);
	//unsigned char* data = nullptr;
	if (data)
	{
		success = true;

		GLuint texture;
		glActiveTexture(activeTexture);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		int texStorageFormat = n == 4 ? GL_RGBA8 : GL_RGB8;
		int texImageFormat = n == 4 ? GL_RGBA : GL_RGB;

		glTexStorage2D(GL_TEXTURE_2D, 0, texStorageFormat, width, height);

		glTexImage2D(GL_TEXTURE_2D, 0, texImageFormat, width, height, 0, texImageFormat, GL_UNSIGNED_BYTE, data);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		TextureInfo info;
		info.activeTexture = activeTexture;
		info.texture = texture;

		m_textures.push_back(info);

		//delete data;
	}

	return success;
}

void Material::SetTextures()
{
	for (TextureInfo info : m_textures)
	{
		glActiveTexture(info.activeTexture);
		glBindTexture(GL_TEXTURE_2D, info.texture);
	}
}