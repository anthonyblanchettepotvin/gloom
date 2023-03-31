#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float constant, float linear, float quadratic)
	: position(position), ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor), constant(constant), linear(linear), quadratic(quadratic)
{
}
