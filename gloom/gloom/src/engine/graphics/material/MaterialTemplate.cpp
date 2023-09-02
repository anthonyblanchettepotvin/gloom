#include "MaterialTemplate.h"

#include <cassert>
#include <stdexcept>

#include "../../EngineHelpers.h"

#include "Material.h"

#define ATTRIBUTE_ALREADY_IN_TEMPLATE "Attribute is already in the template."

MaterialTemplate::MaterialTemplate(Shader& shader)
	: m_Shader(shader)
{
}

void MaterialTemplate::AddAttribute(std::unique_ptr<MaterialAttribute>& attribute)
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

	m_Attributes.push_back(std::move(attribute));
}

Material* MaterialTemplate::CreateMaterialInstance()
{
	std::vector<std::unique_ptr<MaterialAttribute>> attributes;

	for (const auto& attribute : m_Attributes)
	{
		assert(attribute != nullptr);

		attributes.push_back(std::unique_ptr<MaterialAttribute>(attribute->CreateAttributeInstance()));
	}

	return new Material(&m_Shader, attributes);
}
