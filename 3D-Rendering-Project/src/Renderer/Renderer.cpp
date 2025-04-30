#include "pch.hpp"
#include "Renderer.hpp"
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

Renderer::Renderer()
	: m_Camera(vec3(0.0f, 1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), -90.f, 0.0f),
	  running(true)
{
	Init();

	m_baseShader.Init("assets/shaders/basic.vert", "assets/shaders/basic.frag");
	tri.Init(vec3(0.0f, 1.0f, 0.0f));
	tri2.Init(vec3(2.0f, 1.0f, 0.0f));
	m_Grid.Init(vec3(0.0f, 0.0f, -20.0f), 10, 10);
	m_Plane.Init(vec3(0.0f, 0.0f, -10.0f), 5.0f, 5.0f);

	m_Cube.Init(vec3(-2.0f, 0.0f, -2.0f), 0.0f, 0.0f);

	m_lightShader.Init("assets/shaders/light.vert", "assets/shaders/light.frag");

	vec3 pos(0.0f, -4.0f, 0.0f);
	for (auto& cube : m_Cubes)
	{
		cube.Init(pos, 0, 0);
		pos += vec3(1.5f, 1.5f, -1.0f);
	}
}

void Renderer::Init()
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
				m_Camera.processMouseMovement((float)ev.motion.xrel, (float)-ev.motion.yrel);
			}			
		}

		Update(deltaTime);

		Render();

	}
}

void Renderer::Update(float deltaTime)
{
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	if (keys[SDL_SCANCODE_W])
		m_Camera.processKeyboard(1, deltaTime);
	if (keys[SDL_SCANCODE_S])
		m_Camera.processKeyboard(2, deltaTime);
	if (keys[SDL_SCANCODE_A])
		m_Camera.processKeyboard(3, deltaTime);
	if (keys[SDL_SCANCODE_D])
		m_Camera.processKeyboard(4, deltaTime);
	if (keys[SDL_SCANCODE_Q])
		m_Camera.processKeyboard(5, deltaTime);
	if (keys[SDL_SCANCODE_E])
		m_Camera.processKeyboard(6, deltaTime);

	//tri.Update();
	tri2.Update(deltaTime);
	m_Cube.Update();

	//m_Grid.Update(deltaTime);
}

void Renderer::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_baseShader.use();

	mat4 view = m_Camera.getViewMatrix();
	mat4 proj = perspective(radians(90.f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, .01f, 100.0f);


	m_baseShader.setmat4("uModel", tri.getModelMat());
	m_baseShader.setmat4("uView", view);
	m_baseShader.setmat4("uProjection", proj);
	tri.Render(m_window);


	m_baseShader.setmat4("uModel", tri2.getModelMat());
	tri2.Render(m_window);

	//glUseProgram(0);

	m_Grid.Render(m_window, &m_baseShader);
	m_Plane.Render(m_window, view, proj);

	//m_baseShader.setmat4("uModel", m_Cube.getModelMat());
	m_Cube.Render(m_window, view, proj, m_Camera);

	m_lightShader.use();
	m_lightShader.setvec3("light.direction", vec3(-0.2, -1.0f, -0.3f));
	for (uint i = 0; i < 5; i++)
	{
		mat4 model(1.0f);
		model = m_Cubes[i].getModelMat();
		float angle = 20.f * i;
		model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
		m_lightShader.setmat4("uModel", model);
		m_Cubes[i].Render(m_window, view, proj, m_Camera, &m_lightShader);
	}

	SDL_GL_SwapWindow(m_window);
}
