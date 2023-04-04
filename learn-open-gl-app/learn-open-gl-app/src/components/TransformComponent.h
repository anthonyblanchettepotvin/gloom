#pragma once

#include "ActorComponent.h"

#include "glm/glm.hpp"

class TransformComponent : public ActorComponent
{
public:
	TransformComponent(const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f), const glm::vec3& rotation = glm::vec3(0.0f));

	glm::vec3& GetPositionReference() { return position; }
	glm::vec3& GetScaleReference() { return scale; }
	glm::vec3& GetRotationReference() { return rotation; }

	glm::mat4 GetModelTransformationMatrix();
	glm::mat3 GetNormalTransformationMatrix();

private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
};
