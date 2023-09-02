#include "PointLight.h"

PointLight::PointLight(const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor, const PointLightAttenuation& attenuation)
	: m_AmbientColor(ambientColor), m_DiffuseColor(diffuseColor), m_SpecularColor(specularColor), m_Attenuation(attenuation)
{
}
