#pragma once
#include "pch.hpp"
#include "../Drawable.hpp"
#include "../Camera.hpp"
#include "../Shader.hpp"

class Cube
{
public:
	Cube() = default;
	Cube(const vec3& positon, float length, float bredth);
	~Cube();

	void Init(const vec3& positon, float length, float bredth);

	void Update();
	void Render(SDL_Window* window, const mat4& view, const mat4& proj, Camera& cam, Shader* shader = nullptr);

	mat4& getModelMat() { return m_Model; };

private:
	mat4 m_Model = mat4(1.0f);
	Ref<VertexArray> vao;
	Ref<VertexBuffer> vbo;
	Ref<IndexBuffer> ebo;

	Texture diffuse;
	Texture normal;
	Texture specular;
};

class GlobalCube
{
public:
	GlobalCube() = default;

	void Init(const vec3& positon);

	void Update(float dt);

	void Render(SDL_Window* window, const mat4& view, const mat4& proj, glm::vec3& camPos, GlobalShader* shader);

	glm::vec3 getPos() { return glm::vec3(m_Model[3]); }

private:
	mat4 m_Model = mat4(1.f);
	Ref<VertexArray> vao;
	Ref<VertexBuffer> vbo;
	Ref<IndexBuffer> ebo;

	Material material;
};