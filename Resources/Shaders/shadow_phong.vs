#version 430

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexNormal;
layout (location=2) in vec2 vertexTexCoord;

uniform mat4 mxModelView;
uniform mat4 mxMVP;
uniform mat3 mxNormal;
uniform mat4 mxMLP;

out vec3 outFragPosition;
out vec3 outFragNormal;
out vec2 outTexCoord;
out vec4 shadowCoordFragment;

void main()
{
	outFragPosition = vec3(mxModelView * vec4(vertexPosition, 1.0));
	outFragNormal = normalize(mxNormal * vertexNormal);
	outTexCoord = vertexTexCoord;
	shadowCoordFragment = mxMLP * vec4(vertexPosition, 1.0);

	gl_Position = mxMVP * vec4(vertexPosition, 1.0);
}