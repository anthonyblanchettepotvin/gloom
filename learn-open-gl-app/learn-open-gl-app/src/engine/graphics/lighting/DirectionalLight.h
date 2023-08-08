#pragma once

#include <glm/gtc/type_ptr.hpp>

class DirectionalLight
{
public:
	DirectionalLight(const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor);

	glm::vec3 GetDirection() { return direction; }
	glm::vec3& GetDirectionReference() { return direction; };
	void SetDirection(const glm::vec3 direction) { this->direction = direction; };

	glm::vec3 GetAmbientColor() { return ambientColor; }
	glm::vec3& GetAmbientColorReference() { return ambientColor; };
	void SetAmbientColor(const glm::vec3 ambientColor) { this->ambientColor = ambientColor; };

	glm::vec3 GetDiffuseColor() { return diffuseColor; }
	glm::vec3& GetDiffuseColorReference() { return diffuseColor; };
	void SetDiffuseColor(const glm::vec3 diffuseColor) { this->diffuseColor = diffuseColor; };

	glm::vec3 GetSpecularColor() { return specularColor; }
	glm::vec3& GetSpecularColorReference() { return specularColor; };
	void SetSpecularColor(const glm::vec3 specularColor) { this->specularColor = specularColor; };

private:
	glm::vec3 direction = glm::vec3(-1.0f);

	glm::vec3 ambientColor = glm::vec3(0.05f);
	glm::vec3 diffuseColor = glm::vec3(0.4f);
	glm::vec3 specularColor = glm::vec3(0.5f);
};
