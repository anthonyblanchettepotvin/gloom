#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor)
	: m_AmbientColor(ambientColor), m_DiffuseColor(diffuseColor), m_SpecularColor(specularColor)
{
}
