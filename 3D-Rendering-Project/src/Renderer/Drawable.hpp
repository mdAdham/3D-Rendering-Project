#pragma once
#include "pch.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

class Drawable
{
public:
	virtual void Render(SDL_Window* window, const mat4& view, const mat4& proj) = 0;

protected:
	mat4 m_Model;
	Ref<VertexArray> vao;
	Ref<VertexBuffer> vbo;
	Ref<IndexBuffer> ebo;
};