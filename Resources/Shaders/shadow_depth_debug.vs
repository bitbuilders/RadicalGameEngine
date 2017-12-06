#version 430

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec2 texCoordVertex;

out vec2 texCoordFragment;

void main()
{
	texCoordFragment = vec2(texCoordVertex.x, 1.0 - texCoordVertex.y);
	vec3 position = (vertexPosition * 0.4f) + vec3(-0.5f, 0.40f, 0.0f);
	gl_Position = vec4(position, 1.0);
}