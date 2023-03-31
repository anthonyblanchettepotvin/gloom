#pragma once

#include <glm/glm.hpp>

class DirectionalLight
{
public:
	glm::vec3 direction;

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	DirectionalLight(glm::vec3 direction, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor);
};
