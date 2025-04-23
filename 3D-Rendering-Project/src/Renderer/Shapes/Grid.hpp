#pragma once
#include "Square.hpp"
#include "pch.hpp"
#include <vector>
#include "../Shader.hpp"

using namespace std;

class Array
{
public:
	Array() = default;
	Array(const vec3& positon, uint x, mat4 parent = mat4(1.0f));
	~Array();

	void Init(const vec3& positon, uint x, mat4 parent = mat4(1.0f));
	void Update(float dt);
	void Render(SDL_Window* window, Shader* shader);

private:
	mat4 m_ArrayModel;
	vector<Square> m_Array;
};

class Grid
{
public:
	Grid() = default;
	Grid(const vec3& positon, uint x, uint y);
	~Grid();

	void Init(const vec3& positon, uint x, uint y);
	void Update(float dt);
	void Render(SDL_Window* window, Shader* shader);

private:
	mat4 m_GridModel;
	vector<Array> m_Grid;
};