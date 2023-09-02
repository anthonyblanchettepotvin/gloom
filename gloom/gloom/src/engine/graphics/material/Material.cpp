#include "Material.h"

#include <cassert>
#include <stdexcept>

#include "../../EngineHelpers.h"

#include "../shader/Shader.h"

Material::Material(Shader* shader, std::vector<std::unique_ptr<MaterialAttribute>>& attributes)
	: m_Shader(shader)
{
	for (const auto& attribute : attributes)
	{
		if (!attribute)
		{
			throw std::invalid_argument(ARGUMENT_CONTAINS_NULLPTR(attributes));
		}
	}

	m_Attributes = std::move(attributes);
}

std::vector<const MaterialAttribute*> Material::GetAttributes() const
{
	std::vector<const MaterialAttribute*> attributes;

	for (const auto& attribute : m_Attributes)
	{
		assert(attribute != nullptr);

		attributes.push_back(attribute.get());
	}

	return attributes;
}
