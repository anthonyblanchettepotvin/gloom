#include "AssetRegistry.h"

#include <stdexcept>

#include "AssetDescriptor.h"
#include "AssetFactory.h"

#define ASSET_ALREADY_REGISTERED "Asset information matching object type already registered."
#define ASSET_NOT_REGISTERED "Asset information matching object type not registered."

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
		throw std::runtime_error(ASSET_ALREADY_REGISTERED);
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
		throw std::runtime_error(ASSET_NOT_REGISTERED);
	}
}
