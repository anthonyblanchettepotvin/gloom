#include "Material.h"

#include "../shader/Shader.h"

Material::Material(Shader* shader, std::vector<std::unique_ptr<MaterialAttribute>>& attributes)
	: m_Shader(shader), m_Attributes(std::move(attributes))
{
}

std::vector<MaterialAttribute*> Material::GetAttributes() const
{
	std::vector<MaterialAttribute*> attributes;

	for (const auto& attribute : m_Attributes)
	{
		attributes.push_back(attribute.get());
	}

	return attributes;
}
