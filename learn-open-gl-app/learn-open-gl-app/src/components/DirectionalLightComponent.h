#pragma once

#include "LightComponent.h"

class DirectionalLightComponent : public LightComponent
{
public:
	glm::vec3& GetDirectionReference() { return direction; };
	void SetDirection(const glm::vec3 direction) { this->direction = direction; };

	glm::vec3& GetAmbientColorReference() { return ambientColor; };
	void SetAmbientColor(const glm::vec3 ambientColor) { this->ambientColor = ambientColor; };

	glm::vec3& GetDiffuseColorReference() { return diffuseColor; };
	void SetDiffuseColor(const glm::vec3 diffuseColor) { this->diffuseColor = diffuseColor; };

	glm::vec3& GetSpecularColorReference() { return specularColor; };
	void SetSpecularColor(const glm::vec3 specularColor) { this->specularColor = specularColor; };

	void Register(Shader* shader, const std::string& identifier) override;
	void Register(unsigned int& offset) override;

private:
	glm::vec3 direction = glm::vec3(-1.0f);

	glm::vec3 ambientColor = glm::vec3(0.05f);
	glm::vec3 diffuseColor = glm::vec3(0.4f);
	glm::vec3 specularColor = glm::vec3(0.5f);
};
