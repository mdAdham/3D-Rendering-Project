#pragma once
#include "pch.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Run();
private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};