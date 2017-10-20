#version 410

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexNormal;

uniform mat4 mxModelView;
uniform mat4 mxMVP;
uniform mat3 mxNormal;

out vec4 outFragPosition;
out vec3 outFragNormal;

void main()
{
	outFragPosition = mxModelView * vec4(vertexPosition, 1.0);
	outFragNormal = mxNormal * vertexNormal;

	gl_Position = mxMVP * vec4(vertexPosition, 1.0);
}