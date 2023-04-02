#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);

const float DEFAULT_YAW = -90.0f;
const float DEFAULT_PITCH = 0.0f;

const float DEFAULT_MOVEMENT_SPEED = 2.5f;
const float DEFAULT_MOUSE_SENSITIVITY = 0.1f;

const float DEFAULT_FOV = 45.0f;

const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

class Camera
{
public:
	Camera(const glm::vec3& position, int viewWidth, int viewHeight);

	void ProcessKeyboard(CameraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	glm::vec3 GetPosition() { return position; };

	void setViewWidth(int viewWidth) { this->viewWidth = viewWidth; };
	void setViewHeight(int viewHeight) { this->viewHeight = viewHeight; };

private:
	void Update();

	glm::vec3 position;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	float yaw = DEFAULT_YAW;
	float pitch = DEFAULT_PITCH;

	float movementSpeed = DEFAULT_MOVEMENT_SPEED;
	float mouseSensitivity = DEFAULT_MOUSE_SENSITIVITY;

	int viewWidth;
	int viewHeight;
	float fov = DEFAULT_FOV;
};
