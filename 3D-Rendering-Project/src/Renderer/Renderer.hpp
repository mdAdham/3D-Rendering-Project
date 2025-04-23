#pragma once
#include "pch.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

#include "Shapes/Triangle.hpp"
#include "Shapes/Square.hpp"
#include "Shapes/Grid.hpp"
#include "Shapes/Plane.hpp"
#include "Shapes/Cube.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Run();

private:
	void Init();
	void Update(float deltatime);
	void Render();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	Shader m_baseShader;
	Camera m_Camera;

	// Missalaneous
	bool running;
	float m_LastFrame = 0.0f;

	Triangle tri, tri2;
	Grid m_Grid;
	Plane m_Plane, m_Plane2;
	Cube m_Cube;
};