#version 410

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexNormal;

uniform vec3 ambientMaterial;
uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;

uniform mat4 mxModelView;
uniform mat4 mxMVP;
uniform mat3 mxNormal;

uniform vec3 lightPosition;
uniform vec3 lightColor;

out vec3 outVertexColor;

void main()
{
	vec3 ambient = ambientMaterial;
    outVertexColor = ambient;
    gl_Position = vec4(vertexPosition, 1.0);
}