#pragma once
#include "pch.hpp"
#include "../VertexArray.hpp"
#include "../Texture.hpp"
#include "../Shader.hpp"
#include "../Camera.hpp"

class Cube
{
public:
	Cube() = default;
	Cube(const vec3& positon, float length, float bredth);
	~Cube();

	void Init(const vec3& positon, float length, float bredth);

	void Update();
	void Render(SDL_Window* window, const mat4& view, const mat4& proj, Camera& cam, Shader* shader = nullptr);

	mat4 getModelMat() const { return m_Model; };

private:
	mat4 m_Model;
	Ref<VertexArray> vao;
	Ref<VertexBuffer> vbo;
	Ref<IndexBuffer> ebo;

	Texture diffuse;
	Texture normal;
	Texture specular;
	Shader m_shader;
};