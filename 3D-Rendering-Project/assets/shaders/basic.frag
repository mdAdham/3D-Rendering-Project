#version 330 core

in vec4 FragPos;
in vec3 Color;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;
void main()
{
	TexCoord;
	Normal;
	FragPos;
	FragColor = vec4(Color, 1.0);
}