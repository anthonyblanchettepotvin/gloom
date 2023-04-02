#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& direction)
	: direction(direction),
	ambientColor(DEFAULT_DIR_LIGHT_AMBIENT_COLOR),
	diffuseColor(DEFAULT_DIR_LIGHT_DIFFUSE_COLOR),
	specularColor(DEFAULT_DIR_LIGHT_SPECULAR_COLOR)
{
}

void DirectionalLight::Register(Shader& shader, const std::string& identifier)
{
	shader.setFloatVec3(identifier + ".direction", direction);
	shader.setFloatVec3(identifier + ".ambientColor", ambientColor);
	shader.setFloatVec3(identifier + ".diffuseColor", diffuseColor);
	shader.setFloatVec3(identifier + ".specularColor", specularColor);
}
