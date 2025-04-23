#include "pch.hpp"
#include "Grid.hpp"

Array::Array(const vec3& positon, uint x, mat4 parent)
	: m_ArrayModel(parent)
{
	m_ArrayModel = translate(m_ArrayModel, positon);

	m_Array.reserve(x);
	for (size_t _x = 0; _x < (size_t)x; _x++)
	{
		m_Array.emplace_back(m_ArrayModel, vec3((float)_x, 0.0f, 0.0f));
	}
}

Array::~Array()
{
	for (auto& x : m_Array)
	{
		x.~Square();
	}
	
}

void Array::Init(const vec3& positon, uint x, mat4 parent)
{
	m_ArrayModel = parent;
	m_ArrayModel = translate(m_ArrayModel, positon);

	m_Array.reserve(x);
	for (size_t _x = 0; _x < (size_t)x; _x++)
	{
		m_Array.emplace_back(m_ArrayModel, vec3((float)_x, 0.0f, 0.0f));
	}
}

void Array::Update(float dt)
{
	for (size_t _x = 0; _x < m_Array.size(); _x++)
	{
		m_Array[_x].Update(dt);
	}
}

void Array::Render(SDL_Window* window, Shader* shader)
{
	for (size_t _x = 0; _x < m_Array.size(); _x++)
	{
		m_Array[_x].Render(window, shader);
	}
}

Grid::Grid(const vec3& position, uint x, uint y)
	: m_GridModel(1.0f)
{
	m_GridModel = translate(m_GridModel, position);

	m_Grid.reserve(y);

	for (int _y = 0; _y < y; _y++)
	{
		m_Grid.emplace_back(vec3(0.0f, 0.0f, _y), x, m_GridModel);
	}
}

Grid::~Grid()
{
	for (auto& y : m_Grid)
	{
		y.~Array();
	}
}

void Grid::Init(const vec3& position, uint x, uint y)
{
	m_GridModel = mat4(1.0f);
	m_GridModel = translate(m_GridModel, position);

	m_Grid.reserve(y);

	for (int _y = 0; _y < y; _y++)
	{
		m_Grid.emplace_back(vec3(0.0f, 0.0f, _y), x, m_GridModel);
	}
}

void Grid::Update(float dt)
{
	for (int y = 0; y < m_Grid.size(); y++)
	{
		m_Grid[y].Update(dt);
	}
}

void Grid::Render(SDL_Window* window, Shader* shader)
{
	for (int y = 0; y < m_Grid.size(); y++)
	{
		m_Grid[y].Render(window, shader);
	}
}
