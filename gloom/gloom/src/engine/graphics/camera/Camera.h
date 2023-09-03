#pragma once

#include <vector>

#include <glm/glm.hpp>

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

const glm::vec3 WORLD_UP{ 0.0f, 1.0f, 0.0f };

class Camera
{
public:
	Camera(const glm::vec3& position, size_t viewWidth, size_t viewHeight);

	void ProcessKeyboard(CameraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetSkyboxMatrix() const;
	glm::mat4 GetProjectionMatrix() const;

	glm::vec3 GetPosition() const { return m_Position; }

	void SetViewWidth(size_t viewWidth) { m_ViewWidth = viewWidth; }
	void SetViewHeight(size_t viewHeight) { m_ViewHeight = viewHeight; }

private:
	void Update();

	glm::vec3 m_Position{0.0f};

	glm::vec3 m_Forward;
	glm::vec3 m_Right;
	glm::vec3 m_Up;

	float m_Yaw = -90.0f;
	float m_Pitch = 0.0f;
	float m_MinPitch = -89.0f;
	float m_MaxPitch = 89.0f;

	float m_MovementSpeed = 2.5f;
	float m_MouseSensitivity = 0.1f;

	size_t m_ViewWidth;
	size_t m_ViewHeight;
	float m_FieldOfView = 45.0f;
	float m_MinFieldOfView = 1.0f;
	float m_MaxFieldOfView = 90.0f;

	float m_NearClippingDistance = 0.1f;
	float m_FarClippingDistance = 1000.0f;
};
