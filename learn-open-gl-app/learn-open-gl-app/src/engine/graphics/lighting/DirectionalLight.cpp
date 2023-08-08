#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor)
	: ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor)
{
}
