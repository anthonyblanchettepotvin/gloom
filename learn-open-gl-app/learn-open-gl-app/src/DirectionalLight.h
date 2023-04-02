#pragma once

#include <glm/glm.hpp>

#include "Shader.h"

const glm::vec3 DEFAULT_DIR_LIGHT_AMBIENT_COLOR = glm::vec3(0.05f);
const glm::vec3 DEFAULT_DIR_LIGHT_DIFFUSE_COLOR = glm::vec3(0.4f);
const glm::vec3 DEFAULT_DIR_LIGHT_SPECULAR_COLOR = glm::vec3(0.5f);

class DirectionalLight
{
public:
	DirectionalLight(const glm::vec3& direction);

	void Register(Shader& shader, const std::string& identifier);

	void setDirection(const glm::vec3& direction) { this->direction = direction; };
	void setAmbientColor(const glm::vec3 ambientColor) { this->ambientColor = ambientColor; };
	void setDiffuseColor(const glm::vec3 diffuseColor) { this->diffuseColor = diffuseColor; };
	void setSpecularColor(const glm::vec3 specularColor) { this->specularColor = specularColor; };
private:
	glm::vec3 direction;

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
};
