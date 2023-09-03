#include "TransformComponent.h"

#include <glm/ext/matrix_transform.hpp>

TransformComponent::TransformComponent(const glm::vec3& translation, const glm::vec3& scale, const glm::vec3& rotation)
	: m_Tranlastion(translation), m_Scale(scale), m_Rotation(rotation)
{
}

glm::mat4 TransformComponent::GetTransform() const
{
	/* Here, we create our model transformation matrix. This will allows us to transform the
	model vertices which are in local space coordinates into world space coordinates. */
	/* Note that the actual transformation order should be read in reverse: even though in
	code we first translate and then later rotate, the actual transformations first apply
	a rotation and then a translation. The recommended order is: scaling, rotation and then
	translation. Otherwise, the transformations would affect each other in unexpected ways, like
	the translation being scaled. */
	/* Note that glm::value_ptr call is important since glm may store the data
	in a way that doesn't always match OpenGL's expectations. */
	glm::mat4 transform{ 1.0f };
	transform = glm::translate(transform, m_Tranlastion);
	transform = glm::rotate(transform, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, m_Scale);

	return transform;
}
