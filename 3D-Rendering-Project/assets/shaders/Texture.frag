#version 450 core

in vec3 Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
	vec4 texColor = vec4(Color, 1.f);
	texColor *= texture(uTexture, TexCoord);
	FragColor = texColor;
}