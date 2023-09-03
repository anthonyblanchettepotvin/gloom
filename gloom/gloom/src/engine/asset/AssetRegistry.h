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

	AssetRegistryEntry& FindEntry(const ObjectType& objectType);

	std::vector<AssetDescriptor> GetAssetDescriptors() const;

private:
	std::unordered_map<ObjectType, AssetRegistryEntry> m_Entries;
};
