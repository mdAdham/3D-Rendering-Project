#pragma once
#include "pch.hpp"
#include "../Drawable.hpp"

class Plane : public Drawable
{
public:
	Plane() = default;
	Plane(const vec3& positon, float length, float bredth);
	~Plane();

	void Init(const vec3& positon, float length, float bredth);

	void Update();
	void Render(SDL_Window* window, const mat4& view, const mat4& proj);

private:
	Texture tex;
	Shader shader{};
};