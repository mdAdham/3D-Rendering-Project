#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec3 color;

out vec3 Color;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
	Color = color;
}