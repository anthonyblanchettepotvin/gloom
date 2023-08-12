#include "AssetRegistry.h"

#include <stdexcept>

AssetRegistryEntry::AssetRegistryEntry(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory)
	: m_AssetDescriptor(assetDescriptor), m_AssetFactory(std::move(assetFactory))
{
}

void AssetRegistry::RegisterAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory)
{
	AssetType assetType = assetDescriptor.GetAssetType();

	auto it = m_Entries.find(assetType);
	if (it == m_Entries.end())
	{
		m_Entries.emplace(assetType, AssetRegistryEntry(assetDescriptor, assetFactory));
	}
	else
	{
		// TODO: Throw exception
	}
}

const AssetRegistryEntry& AssetRegistry::FindEntry(const AssetType& assetType) const
{
	auto it = m_Entries.find(assetType);
	if (it != m_Entries.end())
	{
		return m_Entries.at(assetType);
	}
	else
	{
		// TODO: Throw exception
	}
}
