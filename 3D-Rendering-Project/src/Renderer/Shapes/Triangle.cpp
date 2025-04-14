#include "pch.hpp"
#include "Triangle.hpp"

Triangle::Triangle(vec3 position)
	: model(1.0f),
	  VBO(0),
	  VAO(0)
{
	model = translate(model, position);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Triangle::Update()
{
	model = rotate(model, 0.005f, vec3(0.0f, 0.0f, 1.0f));
}

void Triangle::Render(SDL_Window* window)
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

mat4 Triangle::getModelMat() const
{
	return model;
}
