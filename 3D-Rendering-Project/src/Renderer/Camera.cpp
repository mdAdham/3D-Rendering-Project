#include "pch.hpp"
#include "Camera.hpp"

Camera::Camera(vec3 position, vec3 up, float yaw, float pitch)
	: front(vec3(0.0f, 0.0f, -1.0f)),
	  worldUp(up),
	  movementSpeed(2.5f),
	  mouseSensitivity(0.04f)
{
	this->position = position;
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();
}

mat4 Camera::getViewMatrix()
{
	return lookAt(position, position + front, up);
}

void Camera::processKeyboard(int direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;

	if (direction == 1)
		position += front * velocity;
	if (direction == 2)
		position -= front * velocity;
	if (direction == 3)
		position -= right* velocity;
	if (direction == 4)
		position += right * velocity;
	if (direction == 5)
		position += up * velocity;
	if (direction == 6)
		position -= up * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset)
{
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	vec3 front;
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));

	this->front = normalize(front);

	right = normalize(cross(this->front, worldUp));
	up = normalize(cross(right, this->front));
}
