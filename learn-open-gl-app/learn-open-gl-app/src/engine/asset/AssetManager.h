#pragma once

#include "AssetRegistry.h"
#include "AssetRepository.h"

class AssetManager
{
public:
	AssetManager(AssetRegistry& assetRegistry, AssetRepository& assetRepository);

	void RegisterAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory);

	Asset* CreateBlankAsset(const AssetType& assetType);

	std::vector<Asset*> FindAssets(const AssetType& assetType);

private:
	AssetRegistry& m_AssetRegistry;
	AssetRepository& m_AssetRepository;
};
