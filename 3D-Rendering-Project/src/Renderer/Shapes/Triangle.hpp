#pragma once
#include "pch.hpp"

using namespace glm;
class Triangle
{
public:
	Triangle(vec3 position);

	void Update();
	void Render(SDL_Window* window);

	mat4 getModelMat() const;
private:
	mat4 model;
	unsigned int VBO, VAO;
};