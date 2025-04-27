#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 FragPos;
out vec3 Color;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
	FragPos = vec3(uModel * vec4(aPos, 1.0));
	//Normal = mat3(transpose(inverse(uModel))) * aNormal;
	Normal = aNormal;
	Color = aColor;
	TexCoord = aTexCoord;

	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}