#include "AssetDescriptor.h"

AssetType::AssetType(const std::type_index& typeIndex)
	: m_TypeIndex(typeIndex)
{
}

AssetDescriptor::AssetDescriptor(const AssetType& assetType, const std::string& displayName)
	: m_AssetType(assetType), m_DisplayName(displayName)
{
}
