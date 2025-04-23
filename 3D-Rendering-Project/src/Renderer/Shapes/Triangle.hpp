#pragma once
#include "pch.hpp"

using namespace glm;
class Triangle
{
public:
	Triangle() = default;
	Triangle(vec3 position);
	~Triangle();

	void Init(vec3 position);

	void Update(float dt);
	void Render(SDL_Window* window);

	mat4 getModelMat() const;
private:
	mat4 model;
	unsigned int VBO, VAO;
};