#include "MaterialAttributes.h"

FloatMaterialAttribute::FloatMaterialAttribute(const std::string& name)
	: MaterialAttribute(name)
{
}

MaterialAttribute* FloatMaterialAttribute::CreateAttributeInstance() const
{
	return new FloatMaterialAttribute(m_Name);
}

TextureMaterialAttribute::TextureMaterialAttribute(const std::string& name)
	: MaterialAttribute(name)
{
}

MaterialAttribute* TextureMaterialAttribute::CreateAttributeInstance() const
{
	return new TextureMaterialAttribute(m_Name);
}

CubemapMaterialAttribute::CubemapMaterialAttribute(const std::string& name)
	: MaterialAttribute(name)
{
}

MaterialAttribute* CubemapMaterialAttribute::CreateAttributeInstance() const
{
	return new CubemapMaterialAttribute(m_Name);
}
