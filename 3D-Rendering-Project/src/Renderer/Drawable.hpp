#pragma once
#include "pch.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

class Drawable
{
public:
	void Render(SDL_Window* window, const mat4& view,
		const mat4& proj) {}

protected:
	mat4 m_Model = mat4(1.f);
	Ref<VertexArray> vao;
	Ref<VertexBuffer> vbo;
	Ref<IndexBuffer> ebo;
};