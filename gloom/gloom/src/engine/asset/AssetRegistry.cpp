#include "AssetRegistry.h"

#include <stdexcept>

#include "AssetDescriptor.h"
#include "AssetFactory.h"

#define ASSET_ALREADY_REGISTERED "Asset information matching object type already registered."
#define ASSET_NOT_REGISTERED "Asset information matching object type not registered."

void AssetRegistry::DefineAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory)
{
	ObjectType objectType = assetDescriptor.GetObjectType();

	auto it = m_Entries.find(objectType);
	if (it != m_Entries.end())
	{
		throw std::runtime_error(ASSET_ALREADY_REGISTERED);
	}

	m_Entries.emplace(objectType, AssetRegistryEntry(assetDescriptor, assetFactory));
}

AssetRegistryEntry& AssetRegistry::FindEntry(const ObjectType& objectType)
{
	auto it = m_Entries.find(objectType);
	if (it == m_Entries.end())
	{
		throw std::runtime_error(ASSET_NOT_REGISTERED);
	}

	return m_Entries.at(objectType);
}

std::vector<AssetDescriptor> AssetRegistry::GetAssetDescriptors() const
{
	std::vector<AssetDescriptor> assetDescriptors;

	for (const auto& entry : m_Entries)
	{
		assetDescriptors.push_back(entry.second.GetDescriptor());
	}

	return assetDescriptors;
}
