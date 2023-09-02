#pragma once

#include <glm/gtc/type_ptr.hpp>

struct PointLightAttenuation {
	float Constant;
	float Linear;
	float Quadratic;
};

class PointLight
{
public:
	PointLight(const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor, const PointLightAttenuation& attenuation);

	void SetPosition(const glm::vec3& position) { m_Position = position; }
	glm::vec3& GetPosition() { return m_Position; }

	void SetAmbientColor(const glm::vec3& ambientColor) { m_AmbientColor = ambientColor; }
	glm::vec3& GetAmbientColor() { return m_AmbientColor; }

	void SetDiffuseColor(const glm::vec3& diffuseColor) { m_DiffuseColor = diffuseColor; }
	glm::vec3& GetDiffuseColor() { return m_DiffuseColor; }

	void SetSpecularColor(const glm::vec3& specularColor) { m_SpecularColor = specularColor; }
	glm::vec3& GetSpecularColor() { return m_SpecularColor; }

	void SetAttenuation(const PointLightAttenuation& attenuation) { m_Attenuation = attenuation; }
	PointLightAttenuation& GetAttenuation() { return m_Attenuation; }

private:
	glm::vec3 m_Position{ 2.0f };

	glm::vec3 m_AmbientColor;
	glm::vec3 m_DiffuseColor;
	glm::vec3 m_SpecularColor;

	PointLightAttenuation m_Attenuation;
};
