#pragma once

#include <glm/gtc/type_ptr.hpp>

struct PointLightAttenuation {
	float constant;
	float linear;
	float quadratic;
};

class PointLight
{
public:
	PointLight(const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor, const PointLightAttenuation& attenuation);

	glm::vec3 GetPosition() { return position; }
	glm::vec3& GetPositionReference() { return position; }
	void SetPosition(const glm::vec3 position) { this->position = position; }

	glm::vec3 GetAmbientColor() { return ambientColor; }
	glm::vec3& GetAmbientColorReference() { return ambientColor; };
	void SetAmbientColor(const glm::vec3 ambientColor) { this->ambientColor = ambientColor; };

	glm::vec3 GetDiffuseColor() { return diffuseColor; }
	glm::vec3& GetDiffuseColorReference() { return diffuseColor; };
	void SetDiffuseColor(const glm::vec3 diffuseColor) { this->diffuseColor = diffuseColor; };

	glm::vec3 GetSpecularColor() { return specularColor; }
	glm::vec3& GetSpecularColorReference() { return specularColor; };
	void SetSpecularColor(const glm::vec3 specularColor) { this->specularColor = specularColor; };

	PointLightAttenuation GetAttenuation() { return attenuation; }
	PointLightAttenuation& GetAttenuationReference() { return attenuation; };
	void SetAttenuation(PointLightAttenuation attenuation) { this->attenuation = attenuation; };

private:
	glm::vec3 position{ 2.0f };

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	PointLightAttenuation attenuation;
};
