#include "MaterialTemplate.h"

#include <cassert>
#include <stdexcept>

#include "../../EngineHelpers.h"

#define ATTRIBUTE_ALREADY_IN_TEMPLATE "Attribute is already in the template."

MaterialTemplate::MaterialTemplate(const Shader& shader)
	: m_Shader(shader)
{
}

void MaterialTemplate::AddAttribute(std::unique_ptr<MaterialAttributeTemplateBase>& attribute)
{
	if (!attribute)
	{
		throw std::invalid_argument(ARGUMENT_IS_NULLPTR(attribute));
	}

	auto it = std::find(m_Attributes.begin(), m_Attributes.end(), attribute);
	if (it != m_Attributes.end())
	{
		throw std::runtime_error(ATTRIBUTE_ALREADY_IN_TEMPLATE);
	}

	m_Attributes.emplace_back(std::move(attribute));
}

std::vector<const MaterialAttributeTemplateBase*> MaterialTemplate::GetAttributes() const
{
	std::vector<const MaterialAttributeTemplateBase*> attributes;

	for (const auto& attribute : m_Attributes)
	{
		assert(attribute != nullptr);

		attributes.push_back(attribute.get());
	}

	return attributes;
}
