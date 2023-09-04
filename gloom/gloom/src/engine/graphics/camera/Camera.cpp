#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../../math/Math.hpp"

Camera::Camera(const glm::vec3& position, size_t viewWidth, size_t viewHeight)
    : m_Position(position), m_ViewWidth(viewWidth), m_ViewHeight(viewHeight)
{
    Update();
}

glm::mat4 Camera::GetViewMatrix() const
{
    /* Here, we create our view transformation matrix. */
    /* Note that we want to rotate and translate the world in the opposite direction
    of where we want the camera to move. This is because OpenGL is a right-handed system. */
    /* Normally, with all the camera properties, we would form a "look at" matrix.
    See https://learnopengl.com/Getting-started/Camera for more details. */
    /* glm::lookAt does all the above for us. */
    return glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

glm::mat4 Camera::GetSkyboxMatrix() const
{
    /* To make it look like it's really far, we don't want the skybox to be affected by the
    translation of the camera. So, we remove the translation by extracting the top-left 3x3 matrix
    of the view transformation matrix. */
    return glm::mat4(glm::mat3(GetViewMatrix()));
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    /* Here, we crate our (perspective) projection transformation matrix. This will allow us to
    project our 3D space coordinates to a 2D space coordinates (i.e., from view space to clip space). */
    return glm::perspective(glm::radians(m_FieldOfView), (float)m_ViewWidth / (float)m_ViewHeight, m_NearClippingDistance, m_FarClippingDistance);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = m_MovementSpeed * deltaTime;

    switch (direction)
    {
    case FORWARD:
        m_Position += m_Forward * velocity;
        break;
    case BACKWARD:
        m_Position -= m_Forward * velocity;
        break;
    case LEFT:
        m_Position -= m_Right * velocity;
        break;
    case RIGHT:
        m_Position += m_Right * velocity;
        break;
    case UP:
        m_Position += WORLD_UP * velocity;
        break;
    case DOWN:
        m_Position -= WORLD_UP * velocity;
        break;
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= m_MouseSensitivity;
    yoffset *= m_MouseSensitivity;

    m_Yaw += xoffset;
    m_Pitch += yoffset;

    /* The pitch needs to be constrained in such a way that users won't
    be able to look higher than 89 degrees (at 90 degrees we get the LookAt flip)
    and also not below -89 degrees. */
    if (constrainPitch)
    {
        m_Pitch = Math::Clamp(m_Pitch, m_MinPitch, m_MaxPitch);
    }

    Update();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    m_FieldOfView -= (float)yoffset;
    m_FieldOfView = Math::Clamp(m_FieldOfView, m_MinFieldOfView, m_MaxFieldOfView);
}

void Camera::Update()
{
    glm::vec3 updatedForward;
    // See https://learnopengl.com/Getting-started/Camera for a reminder of how it works.
    updatedForward.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    updatedForward.y = sin(glm::radians(m_Pitch));
    updatedForward.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Forward = glm::normalize(updatedForward);

    /* Normalize the vectors, because their length gets closer to 0 the
    more you look up or down which results in slower movement. */
    m_Right = glm::normalize(glm::cross(m_Forward, WORLD_UP)); 
    m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
}
