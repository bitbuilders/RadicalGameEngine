#version 430

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexNormal;
layout (location=2) in vec2 vertexTexCoord;
layout (location=3) in vec3 tangentVertex;

uniform mat4 mxModelView;
uniform mat4 mxMVP;
uniform mat3 mxNormal;

uniform vec4 lightPosition;

out vec4 outFragPosition;
out vec3 outFragNormal;
out vec2 outVertexTexCoord;
out vec3 tangentPosition;
out vec3 tangentLightPosition;

void main()
{
	vec3 normal = normalize(mxNormal * vertexNormal);
	vec3 tangent = normalize(mxNormal * tangentVertex);
	vec3 bitangent = cross(normal, tangent);

	mat3 tangentSpace = transpose(mat3(tangent, bitangent, normal));

	tangentLightPosition = tangentSpace * lightPosition.xyz;

	vec3 position = vec3(mxModelView * vec4(vertexPosition, 1.0));
	tangentPosition = tangentSpace * position;

	outFragPosition = mxModelView * vec4(vertexPosition, 1.0);
	outFragNormal = normalize(mxNormal * vertexNormal);

	gl_Position = mxMVP * vec4(vertexPosition, 1.0);

	outVertexTexCoord = vertexTexCoord;
}