#include "Material.h"

#include <cassert>

#include "MaterialTemplate.h"

Material::Material(const MaterialTemplate* materialTemplate)
	: m_MaterialTemplate(materialTemplate)
{
}

void Material::SetMaterialTemplate(const MaterialTemplate* materialTemplate)
{
	m_MaterialTemplate = materialTemplate;

	ResetAttributes();
}

std::vector<const MaterialAttributeBase*> Material::GetAttributes() const
{
	std::vector<const MaterialAttributeBase*> attributes;

	for (const auto& attribute : m_Attributes)
	{
		assert(attribute != nullptr);

		attributes.push_back(attribute.get());
	}

	return attributes;
}

void Material::ResetAttributes()
{
	for (auto& attribute : m_Attributes)
	{
		attribute.release();
	}

	m_Attributes.clear();

	for (const auto& materialTemplateAttribute : m_MaterialTemplate->GetAttributes())
	{
		assert(materialTemplateAttribute != nullptr);

		m_Attributes.emplace_back(std::move(materialTemplateAttribute->InstantiateMaterialAttribute()));
	}
}
