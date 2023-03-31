#pragma once

#include <glm/glm.hpp>

class PointLight
{
public:
	glm::vec3 position;

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	float constant;
	float linear;
	float quadratic;

	PointLight(glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float constant, float linear, float quadratic);
};
