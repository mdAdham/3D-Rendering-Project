#pragma once

#include <array>

#include "Renderer/Light.hpp"
#include "Base.h"
#include "Renderer/Camera.hpp"

struct SDL_Window;

class Scene
{
public:
	Scene() { }
	virtual ~Scene() { }

	virtual bool Update(float deltatime) = 0;
	virtual void Render(SDL_Window* window) = 0;

	void SetCameraUpdate(float x, float y) { m_Camera->processMouseMovement(x, y); }

protected:
	// Light
	DirectionalLight m_dirlight = { };
	std::array<PointLight, 32> m_PointLight = { };
	std::array<SpotLight, 32> m_SpotLight = { };

	// Camera
	Scope<Camera> m_Camera = { };
};