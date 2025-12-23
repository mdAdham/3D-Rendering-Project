#include "pch.hpp"
#include "Renderer.hpp"
#include <iostream>

#include "Scene/ShaderTestingScene.hpp"
#include "Scene/MainScene.hpp"
using namespace std;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

Renderer::Renderer()
	: m_Camera(vec3(0.0f, 1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), -90.f, 0.0f),
	  running(true)
{
	Init();

	mainscene = CreateScope<MainScene>();

}

void Renderer::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		cerr << "SDL could not initialize!";
		exit(-1);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	m_window = SDL_CreateWindow("3d-Rendering-Project",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);


	if (!m_window)
	{
		cerr << "Window could not be created!\nSDL Error: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(-1);
	}
	SDL_GL_SetSwapInterval(1);

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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

Renderer::~Renderer()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Renderer::Run()
{
	SDL_SetRelativeMouseMode(SDL_TRUE);

	while (running)
	{
		float currentFrame = SDL_GetTicks() / 1000.f;
		float deltaTime = currentFrame - m_LastFrame;
		m_LastFrame = currentFrame;
		SDL_Event ev{};

		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				running = false;

			if (ev.type == SDL_MOUSEMOTION)
			{
				mainscene->SetCameraUpdate((float) ev.motion.xrel, -(float)ev.motion.yrel);
			}			
		}

		Update(deltaTime);

		Render();

	}
}

void Renderer::Update(float deltaTime)
{
	if (!mainscene->Update(deltaTime))
		running = false;
}

void Renderer::Render()
{

	mainscene->Render(m_window);
}
