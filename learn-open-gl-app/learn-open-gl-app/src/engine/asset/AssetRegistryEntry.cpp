#include "AssetRegistryEntry.h"

#include <stdexcept>

#include "AssetFactory.h"

#define NULL_ASSET_FACTORY_ERROR "Asset factory is null."

AssetRegistryEntry::AssetRegistryEntry(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory)
	: m_AssetDescriptor(assetDescriptor)
{
	if (!assetFactory)
	{
		throw std::invalid_argument(NULL_ASSET_FACTORY_ERROR);
	}

	m_AssetFactory = std::move(assetFactory);
}
