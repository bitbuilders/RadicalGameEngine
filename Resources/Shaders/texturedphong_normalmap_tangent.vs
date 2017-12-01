#version 430

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexNormal;
layout (location=2) in vec2 vertexTexCoord;
layout (location=3) in vec3 tangentVertex;

uniform mat4 mxModelView;
uniform mat4 mxMVP;
uniform mat3 mxNormal;

out vec4 outFragPosition;
out vec3 outFragNormal;
out vec2 outVertexTexCoord;

void main()
{
	outFragPosition = mxModelView * vec4(vertexPosition, 1.0);
	outFragNormal = normalize(mxNormal * vertexNormal);

	gl_Position = mxMVP * vec4(vertexPosition, 1.0);

	outVertexTexCoord = vertexTexCoord;
}