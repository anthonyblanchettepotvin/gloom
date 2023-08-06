#include "Material.h"

#include "../../../game/asset/shader/Shader.h"

Material::Material(Shader& shader, std::vector<std::unique_ptr<MaterialAttribute>>& attributes)
	: m_Shader(shader), m_Attributes(std::move(attributes))
{
}

void Material::Use()
{
	m_Shader.Use();

	for (const auto& attribute : m_Attributes)
	{
		m_Shader.SetAttribute(*attribute);
	}
}
