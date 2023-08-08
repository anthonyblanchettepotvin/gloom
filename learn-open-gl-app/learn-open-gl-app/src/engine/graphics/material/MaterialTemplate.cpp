#include "MaterialTemplate.h"

MaterialTemplate::MaterialTemplate(Shader& shader)
	: m_Shader(shader)
{
}

void MaterialTemplate::AddAttribute(std::unique_ptr<MaterialAttribute>& attribute)
{
	auto it = std::find(m_Attributes.begin(), m_Attributes.end(), attribute);
	if (it == m_Attributes.end())
	{
		m_Attributes.push_back(std::move(attribute));
	}
}

Material* MaterialTemplate::CreateMaterialInstance() const
{
	std::vector<std::unique_ptr<MaterialAttribute>> attributes;
	for (const auto& attribute : m_Attributes)
	{
		attributes.push_back(std::unique_ptr<MaterialAttribute>(attribute->CreateAttributeInstance()));
	}

	return new Material(m_Shader, attributes);
}
