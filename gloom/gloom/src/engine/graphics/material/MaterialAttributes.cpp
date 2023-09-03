#include "MaterialAttributes.h"

#include "../cubemap/Cubemap.h"
#include "../texture/Texture.h"

FloatMaterialAttribute::FloatMaterialAttribute(const std::string& name)
	: MaterialAttribute(name)
{
}

MaterialAttribute* FloatMaterialAttribute::CreateAttributeInstance()
{
	return new FloatMaterialAttribute(m_Name);
}

TextureMaterialAttribute::TextureMaterialAttribute(const std::string& name)
	: MaterialAttribute(name)
{
}

MaterialAttribute* TextureMaterialAttribute::CreateAttributeInstance()
{
	return new TextureMaterialAttribute(m_Name);
}

CubemapMaterialAttribute::CubemapMaterialAttribute(const std::string& name)
	: MaterialAttribute(name)
{
}

MaterialAttribute* CubemapMaterialAttribute::CreateAttributeInstance()
{
	return new CubemapMaterialAttribute(m_Name);
}
