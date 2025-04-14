#include "pch.hpp"
#include "Renderer.hpp"
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

Renderer::Renderer()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		cerr << "SDL could not initialize!";
		exit(-1);
	}

	m_window = SDL_CreateWindow("3d-Rendering-Project",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);


	if (!m_window)
	{
		cerr << "Window could not be created!\nSDL Error: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(-1);
	}

	m_glContext = SDL_GL_CreateContext(m_window);

	if (!m_glContext)
	{
		cerr << "OpenGl context could not be created!\nSDL Error: " << SDL_GetError() << endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		exit(-1);
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		cerr << "Failed to initialize GLAD!" << endl;

		SDL_GL_DeleteContext(m_glContext);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		exit(-1);
	}
}

Renderer::~Renderer()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Renderer::Run()
{
}
