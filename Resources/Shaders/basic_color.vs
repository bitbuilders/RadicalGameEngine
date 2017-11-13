#version 410

layout (location=0) in vec3 vertexPosition;
//layout (location=1) in vec3 vertexColor;

uniform vec3 color;
uniform mat4 mxMVP;

out vec3 outVertexColor;

void main()
{
   //outVertexColor = vertexColor;
   outVertexColor = color;
   gl_Position = mxMVP * vec4(vertexPosition, 1.0);
}