#pragma once
#include "pch.hpp"
#include "../VertexArray.hpp"
#include "../Texture.hpp"
#include "../Shader.hpp"

class Light
{
public:
	Light() = default;
	Light(const vec3& positon, const vec3& color);
	~Light();

	void Init(const vec3& positon, const vec3& color);

	void Update();
	void Render(SDL_Window* window, const mat4& view, const mat4& proj);

	mat4 getModelMat() const { return m_Model; };

private:
	mat4 m_Model;
	Ref<VertexArray> vao;
	Ref<VertexBuffer> vbo;
	Ref<IndexBuffer> ebo;

	Shader m_lightshader;

	vec3 lightPos;
	vec3 m_Color;
};