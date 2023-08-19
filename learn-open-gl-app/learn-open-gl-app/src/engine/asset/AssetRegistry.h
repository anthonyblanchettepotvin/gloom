#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "AssetRegistryEntry.h"

class AssetDescriptor;
class AssetFactory;
class ObjectType;

class AssetRegistry
{
public:
	void DefineAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory);

	const AssetRegistryEntry& FindEntry(const ObjectType& objectType) const;

	std::vector<AssetDescriptor> GetAssetDescriptors() const;

private:
	std::unordered_map<ObjectType, AssetRegistryEntry> m_Entries;
};
