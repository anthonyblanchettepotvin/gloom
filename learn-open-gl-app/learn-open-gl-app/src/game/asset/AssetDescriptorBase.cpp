#include "AssetDescriptorBase.h"

AssetDescriptorBase::AssetDescriptorBase(const std::type_index& assetType)
	: m_AssetType(assetType)
{
}

AssetDescriptorBase::AssetDescriptorBase(const AssetDescriptorBase& other)
	: m_AssetType(other.m_AssetType)
{
}
