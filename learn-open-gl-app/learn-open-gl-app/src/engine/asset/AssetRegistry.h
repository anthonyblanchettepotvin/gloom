#pragma once

#include <memory>
#include <unordered_map>

#include "../object/ObjectType.h"

#include "AssetDescriptor.h"
#include "AssetFactory.h"

class AssetRegistryEntry
{
public:
	AssetRegistryEntry(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory);

	AssetDescriptor GetDescriptor() const { return m_AssetDescriptor; }

	const AssetFactory& GetFactory() const { return *m_AssetFactory; }

private:
	AssetDescriptor m_AssetDescriptor;

	std::unique_ptr<AssetFactory> m_AssetFactory = nullptr;
};

class AssetRegistry
{
public:
	void RegisterAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory);

	const AssetRegistryEntry& FindEntry(const ObjectType& objectType) const;

private:
	std::unordered_map<ObjectType, AssetRegistryEntry> m_Entries;
};
