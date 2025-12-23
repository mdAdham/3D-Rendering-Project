#include "pch.hpp"
#include "ShaderTestingScene.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

void ShaderTestingScene::InitLights()
{
	this->m_dirlight.ambient = vec3(0.15f, 0.15f, 0.15f);
	this->m_dirlight.diffuse = vec3(0.2f, 0.2f, 0.2f);
	this->m_dirlight.direction = vec3(-0.7f, -0.2f, -0.4f);
	this->m_dirlight.specular = vec3(0.2f, 0.2f, 0.2f);

	this->m_PointLight[0].constant = 1.0f;
	this->m_PointLight[0].linear = 0.09f;
	this->m_PointLight[0].quadratic = 0.032f;

	this->m_PointLight[0].position = vec3(-2.f, 1.f, 2.f);
	this->m_PointLight[0].ambient = vec3(0.2f, 0.05f, 0.03f);
	this->m_PointLight[0].diffuse = vec3(0.6f, 0.3f, 0.2f);
	this->m_PointLight[0].speclar = vec3(1.0f, 1.0f, 1.0f);

	this->m_PointLight[1].constant = 1.0f;
	this->m_PointLight[1].linear = 0.14f;
	this->m_PointLight[1].quadratic = 0.7f;

	this->m_PointLight[1].position = vec3(2.f, -1.f, -2.f);
	this->m_PointLight[1].ambient = vec3(0.2f, 0.05f, 0.03f);
	this->m_PointLight[1].diffuse = vec3(0.6f, 0.6f, 0.6f);
	this->m_PointLight[1].speclar = vec3(1.0f, 1.0f, 1.0f);

}

ShaderTestingScene::ShaderTestingScene()
{
	this->m_Camera = CreateScope<Camera>(vec3(0.0f, 1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), -90.f, 0.0f);
	InitLights();

	cube.Init(vec3(0.0f, 0.0f, 0.0f));
	shader.InitGlobalShader("assets/shaders/FullShader.vert", "assets/shaders/FullShader.frag");

	shader.SetDirectionalLight(m_dirlight);
	shader.SetPointLight(m_PointLight);
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

	cube.Update(deltaTime);

	//this->m_PointLight[0].position = m_Camera->getPos();
	//shader.SetPointLight(m_PointLight);

	//cout << "Distance b/w camera and object" << glm::length(cube.getPos() - m_Camera->getPos()) << '\n';

	return true;
}

void ShaderTestingScene::Render(SDL_Window* window)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 view = m_Camera->getViewMatrix();
	mat4 proj = glm::perspective(radians(90.f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, .01f, 100.0f);


	cube.Render(window, view, proj, m_Camera->getPos(), &shader);

	SDL_GL_SwapWindow(window);
}
