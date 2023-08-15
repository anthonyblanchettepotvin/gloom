#include "AssetRegistryEntry.h"

#include <cassert>

#include "AssetFactory.h"

AssetRegistryEntry::AssetRegistryEntry(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory)
	: m_AssetDescriptor(assetDescriptor)
{
	assert(assetFactory != nullptr);

	m_AssetFactory = std::move(assetFactory);
}
