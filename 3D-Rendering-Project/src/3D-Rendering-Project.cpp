#include "pch.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/Shapes/Triangle.hpp"

using namespace std;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

/*float verticies[] =
{
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f
};
*/

float verticies[] =
{
	-0.1f, -0.1f, 0.0f,
	 0.1f, -0.1f, 0.0f,
	 0.1f,  0.1f, 0.0f
};

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		cerr << "SDL could not initialize!";
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("3d-Rendering-Project",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);


	if (!window)
	{
		cerr << "Window could not be created!\nSDL Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return -1;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	if (!glContext)
	{
		cerr << "OpenGl context could not be created!\nSDL Error: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		cerr << "Failed to initialize GLAD!" << endl;

		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	Shader shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");

#pragma region CODE

	Camera camera(vec3(0.0f, 1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), -90.f, 0.0f);
	float lastFrame = 0.0f;

	SDL_SetRelativeMouseMode(SDL_TRUE);
#pragma endregion
	Triangle tri(vec3(0.0f, 0.0f, 0.0f)), tri2(vec3(2.0f, 0.0f, 0.0f));

	glFrontFace(GL_FRONT);
	glCullFace(GL_BACK);
	//main loop
	bool running = true;
	while (running)
	{
		float currentFrame = SDL_GetTicks() / 1000.0f;
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				running = false;

			if (ev.type == SDL_MOUSEMOTION)
			{
				camera.processMouseMovement(ev.motion.xrel, -ev.motion.yrel);
			}
		}

#pragma region KEYBOARD
		const Uint8* keys = SDL_GetKeyboardState(nullptr);
		if (keys[SDL_SCANCODE_W])
			camera.processKeyboard(1, deltaTime);
		if (keys[SDL_SCANCODE_S])
			camera.processKeyboard(2, deltaTime);
		if (keys[SDL_SCANCODE_A])
			camera.processKeyboard(3, deltaTime);
		if (keys[SDL_SCANCODE_D])
			camera.processKeyboard(4, deltaTime);
		if (keys[SDL_SCANCODE_Q])
			camera.processKeyboard(5, deltaTime);
		if (keys[SDL_SCANCODE_E])
			camera.processKeyboard(6, deltaTime);

		//tri.Update();
		tri2.Update();
#pragma endregion

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
#pragma region RENDERING
		
		mat4 view = camera.getViewMatrix();
		mat4 proj = perspective(radians(90.f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, .01f, 100.0f);
		

		shader.setmat4("uModel", tri.getModelMat());
		shader.setmat4("uView", view);
		shader.setmat4("uProjection", proj);

		tri.Render(window);
		shader.setmat4("uModel", tri2.getModelMat());
		tri2.Render(window);
#pragma endregion


		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}