#pragma once

#include "Scene.hpp"
#include "../Shapes/Cube.hpp"
#include "../Shader.hpp"

class ShaderTestingScene : public Scene
{
public:
	ShaderTestingScene();

	bool Update(float deltatime) override;
	void Render(SDL_Window* window) override;

private:
	void InitLights();

private:
	GlobalCube cube;
	GlobalShader shader;
};