#pragma once
#include "pch.hpp"
#include "../VertexArray.hpp"
#include "../Texture.hpp"
#include "../Shader.hpp"

class Cube
{
public:
	Cube() = default;
	Cube(const vec3& positon, float length, float bredth);
	~Cube();

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