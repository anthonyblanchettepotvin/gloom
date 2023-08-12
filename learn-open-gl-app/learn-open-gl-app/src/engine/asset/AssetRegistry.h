#pragma once

#include <memory>
#include <unordered_map>

#include "AssetRegistryEntry.h"

class AssetDescriptor;
class AssetFactory;
class ObjectType;

class AssetRegistry
{
public:
	void RegisterAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory);

	const AssetRegistryEntry& FindEntry(const ObjectType& objectType) const;

private:
	std::unordered_map<ObjectType, AssetRegistryEntry> m_Entries;
};
