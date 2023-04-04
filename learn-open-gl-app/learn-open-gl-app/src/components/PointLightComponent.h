#pragma once

#include "glm/glm.hpp"

#include "LightComponent.h"

struct LightAttenuation {
	float constant;
	float linear;
	float quadratic;
};

class PointLightComponent : public LightComponent
{
public:
	glm::vec3& GetAmbientColorReference() { return ambientColor; };
	void SetAmbientColor(const glm::vec3 ambientColor) { this->ambientColor = ambientColor; };

	glm::vec3& GetDiffuseColorReference() { return diffuseColor; };
	void SetDiffuseColor(const glm::vec3 diffuseColor) { this->diffuseColor = diffuseColor; };

	glm::vec3& GetSpecularColorReference() { return specularColor; };
	void SetSpecularColor(const glm::vec3 specularColor) { this->specularColor = specularColor; };

	LightAttenuation& GetLightAttenuationReference() { return attenuation; };
	void SetAttenuation(LightAttenuation attenuation) { this->attenuation = attenuation; };

	void Register(Shader* shader, const std::string& identifier) override;

private:
	glm::vec3 ambientColor = glm::vec3(0.2f);
	glm::vec3 diffuseColor = glm::vec3(0.5f);
	glm::vec3 specularColor = glm::vec3(1.0f);

	LightAttenuation attenuation = LightAttenuation{ 1.0f, 0.14f, 0.07f };
};
