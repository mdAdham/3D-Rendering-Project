#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera
{
public:
	Camera(vec3 position, vec3 up, float yaw, float pitch);

	mat4 getViewMatrix();

	void processKeyboard(int direction, float deltaTime);

	void processMouseMovement(float xOffset, float yOffset);

private:
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 worldUp;

	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSensitivity;

	void updateCameraVectors();
};