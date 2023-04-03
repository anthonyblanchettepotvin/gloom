#pragma once

#include <glm/glm.hpp>

#include "Model.h"
#include "Shader.h"

class Actor
{
public:
	Actor(const glm::vec3& position, Model* model);
	
	void Draw(Shader& shader);

private:
	glm::mat4 GetModelTransformationMatrix();
	glm::mat3 GetNormalTransformationMatrix();

	glm::vec3 position;

	Model* model;
};
