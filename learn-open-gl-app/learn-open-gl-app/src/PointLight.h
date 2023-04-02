#pragma once

#include <glm/glm.hpp>

#include "Shader.h"
#include "Model.h"

struct LightAttenuation {
	float constant;
	float linear;
	float quadratic;
};

const glm::vec3 DEFAULT_POINT_LIGHT_AMBIENT_COLOR = glm::vec3(0.2f);
const glm::vec3 DEFAULT_POINT_LIGHT_DIFFUSE_COLOR = glm::vec3(0.5f);
const glm::vec3 DEFAULT_POINT_LIGHT_SPECULAR_COLOR = glm::vec3(1.0f);
const LightAttenuation DEFAULT_POINT_LIGHT_ATTENUATION = LightAttenuation{ 1.0f, 0.14f, 0.07f };

class PointLight
{
public:
	PointLight(const glm::vec3& position, Model* model);

	void Draw(Shader& shader);
	void Register(Shader& shader, const std::string& identifier);

	void setPosition(const glm::vec3& position) { this->position = position; };
	void setAmbientColor(const glm::vec3 ambientColor) { this->ambientColor = ambientColor; };
	void setDiffuseColor(const glm::vec3 diffuseColor) { this->diffuseColor = diffuseColor; };
	void setSpecularColor(const glm::vec3 specularColor) { this->specularColor = specularColor; };
	void setAttenuation(LightAttenuation attenuation) { this->attenuation = attenuation; };
private:
	glm::mat4 GetModelTransformationMatrix();

	glm::vec3 position;

	Model* model;

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	LightAttenuation attenuation;
};
