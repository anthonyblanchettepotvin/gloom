#pragma once

#include <glm/gtc/type_ptr.hpp>

class DirectionalLight
{
public:
	DirectionalLight(const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor);

	void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
	glm::vec3& GetDirection() { return m_Direction; }

	void SetAmbientColor(const glm::vec3& ambientColor) { m_AmbientColor = ambientColor; }
	glm::vec3& GetAmbientColor() { return m_AmbientColor; }

	void SetDiffuseColor(const glm::vec3& diffuseColor) { m_DiffuseColor = diffuseColor; }
	glm::vec3& GetDiffuseColor() { return m_DiffuseColor; }

	void SetSpecularColor(const glm::vec3& specularColor) { m_SpecularColor = specularColor; }
	glm::vec3& GetSpecularColor() { return m_SpecularColor; }

private:
	glm::vec3 m_Direction{ -1.0f };

	glm::vec3 m_AmbientColor{ 0.05f };
	glm::vec3 m_DiffuseColor{ 0.4f };
	glm::vec3 m_SpecularColor{ 0.5f };
};
