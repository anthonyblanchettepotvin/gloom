#include "Camera.h"

Camera::Camera(const glm::vec3& position, int viewWidth, int viewHeight)
    : position(position), viewWidth(viewWidth), viewHeight(viewHeight)
{
    Update();
}

glm::mat4 Camera::GetViewMatrix()
{
    /* Here, we create our view transformation matrix. */
    /* Note that we want to rotate and translate the world in the opposite direction
    of where we want the camera to move. This is because OpenGL is a right-handed system. */
    /* Normally, with all the camera properties, we would form a "look at" matrix.
    See https://learnopengl.com/Getting-started/Camera for more details. */
    /* glm::lookAt does all the above for us. */
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
    /* Here, we crate our (perspective) projection transformation matrix. This will allow us to
    project our 3D space coordinates to a 2D space coordinates (i.e., from view space to clip space). */
    return glm::perspective(glm::radians(fov), (float)viewWidth / (float)viewHeight, 0.1f, 100.0f);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
    if (direction == UP)
        position += WORLD_UP * velocity;
    if (direction == DOWN)
        position -= WORLD_UP * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    /* The pitch needs to be constrained in such a way that users won't
    be able to look higher than 89 degrees (at 90 degrees we get the LookAt flip)
    and also not below -89 degrees. */
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    Update();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    fov -= (float)yoffset;

    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void Camera::Update()
{
    glm::vec3 updatedFront;
    // See https://learnopengl.com/Getting-started/Camera for a reminder of how it works.
    updatedFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    updatedFront.y = sin(glm::radians(pitch));
    updatedFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(updatedFront);

    /* Normalize the vectors, because their length gets closer to 0 the
    more you look up or down which results in slower movement. */
    right = glm::normalize(glm::cross(front, WORLD_UP)); 
    up = glm::normalize(glm::cross(right, front));
}
