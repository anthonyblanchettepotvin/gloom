#pragma once

#include <glm/glm.hpp>

#include "ActorComponent.h"

class TransformComponent : public ActorComponent
{
public:
	TransformComponent(const glm::vec3& translation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));

	glm::mat4 GetTransform() const;

	glm::vec3& GetTranslation() { return m_Tranlastion; }
	glm::vec3& GetScale() { return m_Scale; }
	glm::vec3& GetRotation() { return m_Rotation; }

private:
	glm::vec3 m_Tranlastion;
	glm::vec3 m_Scale;
	glm::vec3 m_Rotation;
};
