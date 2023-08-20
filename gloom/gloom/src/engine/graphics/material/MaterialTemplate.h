#pragma once

#include <memory>
#include <vector>

#include "Material.h"
#include "MaterialAttribute.h"

class Shader;

class MaterialTemplate
{
public:
	MaterialTemplate(Shader& shader);

	void AddAttribute(std::unique_ptr<MaterialAttribute>& attribute);

	Material* CreateMaterialInstance() const;

private:
	Shader& m_Shader;

	std::vector<std::unique_ptr<MaterialAttribute>> m_Attributes;
};
