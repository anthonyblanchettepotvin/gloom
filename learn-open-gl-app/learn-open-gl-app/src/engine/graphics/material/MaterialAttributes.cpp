#include "MaterialAttributes.h"

#include "../../../game/asset/shader/Shader.h"

FloatMaterialAttribute::FloatMaterialAttribute(const std::string& name)
	: MaterialAttribute(name)
{
}

std::unique_ptr<MaterialAttribute> FloatMaterialAttribute::CreateAttributeInstance() const
{
	return std::make_unique<FloatMaterialAttribute>(m_Name);
}

TextureMaterialAttribute::TextureMaterialAttribute(const std::string& name)
	: MaterialAttribute(name)
{
}

std::unique_ptr<MaterialAttribute> TextureMaterialAttribute::CreateAttributeInstance() const
{
	return std::make_unique<TextureMaterialAttribute>(m_Name);
}

CubemapMaterialAttribute::CubemapMaterialAttribute(const std::string& name)
	: MaterialAttribute(name)
{
}

std::unique_ptr<MaterialAttribute> CubemapMaterialAttribute::CreateAttributeInstance() const
{
	return std::make_unique<CubemapMaterialAttribute>(m_Name);
}
