#include "pch.hpp"
#include "ShaderTestingScene.hpp"

void ShaderTestingScene::InitLights()
{
	this->m_dirlight.ambient = vec3(0.1f, 0.1f, 0.1f);
	this->m_dirlight.diffuse = vec3(0.5f, 0.5f, 0.5f);
	this->m_dirlight.direction = vec3(1.f, 0.f, 0.f);
	this->m_dirlight.specular = vec3(0.2f, 0.2f, 0.2f);
}

ShaderTestingScene::ShaderTestingScene()
{
	this->m_Camera = CreateScope<Camera>(vec3(0.0f, 1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), -90.f, 0.0f);
	InitLights();
}

bool ShaderTestingScene::Update(float deltaTime)
{
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	if (keys[SDL_SCANCODE_ESCAPE])
		return false;
	if (keys[SDL_SCANCODE_W])
		m_Camera->processKeyboard(1, deltaTime);
	if (keys[SDL_SCANCODE_S])
		m_Camera->processKeyboard(2, deltaTime);
	if (keys[SDL_SCANCODE_A])
		m_Camera->processKeyboard(3, deltaTime);
	if (keys[SDL_SCANCODE_D])
		m_Camera->processKeyboard(4, deltaTime);
	if (keys[SDL_SCANCODE_Q])
		m_Camera->processKeyboard(5, deltaTime);
	if (keys[SDL_SCANCODE_E])
		m_Camera->processKeyboard(6, deltaTime);

	return true;
}

void ShaderTestingScene::Render(SDL_Window* window)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);






	SDL_GL_SwapWindow(window);
}
