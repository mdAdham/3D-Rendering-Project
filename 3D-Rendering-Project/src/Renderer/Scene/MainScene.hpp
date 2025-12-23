#pragma once

#include "Scene.hpp"
#include "Renderer/Shapes/Triangle.hpp"
#include "Renderer/Shapes/Square.hpp"
#include "Renderer/Shapes/Grid.hpp"
#include "Renderer/Shapes/Plane.hpp"
#include "Renderer/Shapes/Cube.hpp"
#include "Renderer/AllLight.hpp"

class MainScene : public Scene
{
public:
	MainScene();

	bool Update(float deltatime) override;
	void Render(SDL_Window* window) override;

private:
	Shader m_baseShader, m_lightShader;
	Shader FullShader;

	Triangle tri, tri2;
	Grid m_Grid;
	Plane m_Plane, m_Plane2;
	Cube m_Cube, m_Cubes[5];

	float dt = 0;
};