#pragma once
#include "pch.hpp"
#include "../Shader.hpp"

using namespace glm;
class Square
{
public:
	Square() = default;
	Square(vec3 position);
	Square(const mat4& parent, const vec3& offset);
	~Square();

	void Init(vec3 position);

	void Update(float dt);
	void Render(SDL_Window* window);
	void Render(SDL_Window* window, Shader* shader);

	mat4 getModelMat() const;
private:
	mat4 model;
	unsigned int VBO, VAO, EBO;
};