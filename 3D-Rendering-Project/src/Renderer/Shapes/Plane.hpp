#pragma once
#include "pch.hpp"
#include "../Shader.hpp"
#include "../VertexArray.hpp"
#include "../Texture.hpp"

class Plane
{
public:
	Plane() = default;
	Plane(const vec3& positon, float length, float bredth);
	~Plane();

	void Init(const vec3& positon, float length, float bredth);

	void Update();
	void Render(SDL_Window* window, const mat4& view, const mat4& proj);

private:
	mat4 m_Model;
	Ref<VertexArray> vao;
	Ref<VertexBuffer> vbo;
	Ref<IndexBuffer> ebo;

	Texture tex;
	Shader shader{};
};