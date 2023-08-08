#include "PointLight.h"

PointLight::PointLight(const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor, const PointLightAttenuation& attenuation)
	: ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor), attenuation(attenuation)
{
}
