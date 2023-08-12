#include "AssetRegistry.h"

#include <stdexcept>

AssetRegistryEntry::AssetRegistryEntry(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory)
	: m_AssetDescriptor(assetDescriptor), m_AssetFactory(std::move(assetFactory))
{
	// TODO: Verify that assetFactory isn't empty
}

void AssetRegistry::RegisterAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory)
{
	ObjectType objectType = assetDescriptor.GetObjectType();

	auto it = m_Entries.find(objectType);
	if (it == m_Entries.end())
	{
		m_Entries.emplace(objectType, AssetRegistryEntry(assetDescriptor, assetFactory));
	}
	else
	{
		// TODO: Throw exception
	}
}

const AssetRegistryEntry& AssetRegistry::FindEntry(const ObjectType& objectType) const
{
	auto it = m_Entries.find(objectType);
	if (it != m_Entries.end())
	{
		return m_Entries.at(objectType);
	}
	else
	{
		// TODO: Throw exception
	}
}
