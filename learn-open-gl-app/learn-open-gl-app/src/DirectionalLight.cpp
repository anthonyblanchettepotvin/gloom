#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor)
	: direction(direction), ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor)
{
}
