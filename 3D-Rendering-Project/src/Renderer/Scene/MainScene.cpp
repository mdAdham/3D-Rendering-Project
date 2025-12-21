#include "pch.hpp"
#include "MainScene.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

MainScene::MainScene()
{
	this->m_Camera = CreateScope<Camera>(vec3(0.0f, 1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), -90.f, 0.0f);



	m_baseShader.Init("assets/shaders/basic.vert", "assets/shaders/basic.frag");
	tri.Init(vec3(0.0f, 1.0f, 0.0f));
	tri2.Init(vec3(2.0f, 1.0f, 0.0f));
	m_Grid.Init(vec3(0.0f, 0.0f, -20.0f), 10, 10);
	m_Plane.Init(vec3(0.0f, 0.0f, -10.0f), 5.0f, 5.0f);

	m_Cube.Init(vec3(-2.0f, 0.0f, -2.0f), 0.0f, 0.0f);

	m_lightShader.Init("assets/shaders/light.vert", "assets/shaders/light.frag");

	m_light.Init(vec3(3.0f, 0.0f, -5.0f), vec3(1.0f, 1.0f, 1.0f));

	vec3 pos(0.0f, -4.0f, 0.0f);
	for (auto& cube : m_Cubes)
	{
		cube.Init(pos, 0, 0);
		pos += vec3(1.5f, 1.5f, -1.0f);
	}
}

bool MainScene::Update(float deltaTime)
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

	tri2.Update(deltaTime);
	m_Cube.Update();

	return true;
}

void MainScene::Render(SDL_Window* m_window)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_baseShader.use();

	mat4 view = m_Camera->getViewMatrix();
	mat4 proj = glm::perspective(radians(90.f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, .01f, 100.0f);


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

	m_lightShader.use();
	m_lightShader.setvec3("light.direction", vec3(-0.2, -1.0f, -0.3f));
	for (uint i = 0; i < 5; i++)
	{
		mat4 model(1.0f);
		model = m_Cubes[i].getModelMat();
		float angle = 20.f * i;
		model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
		m_lightShader.setmat4("uModel", model);
		m_Cubes[i].Render(m_window, view, proj, *m_Camera, &m_lightShader);
	}

	m_light.Render(m_window, view, proj);
	m_Cube.Render(m_window, view, proj, *m_Camera);

	SDL_GL_SwapWindow(m_window);
}
