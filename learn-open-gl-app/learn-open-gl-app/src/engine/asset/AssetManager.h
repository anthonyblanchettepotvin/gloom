#pragma once

#include "AssetRegistry.h"
#include "AssetRepository.h"

class AssetManager
{
public:
	AssetManager(AssetRegistry& assetRegistry, AssetRepository& assetRepository);

	void RegisterAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory);

	template<class T>
	Asset* CreateBlankAsset();
	Asset* CreateBlankAsset(const AssetType& assetType);

	template<class T>
	std::vector<Asset*> FindAssets();
	std::vector<Asset*> FindAssets(const AssetType& assetType);

private:
	AssetRegistry& m_AssetRegistry;
	AssetRepository& m_AssetRepository;
};

template<class T>
inline Asset* AssetManager::CreateBlankAsset()
{
	AssetType assetType(typeid(T));

	return CreateBlankAsset(assetType);
}

template<class T>
inline std::vector<Asset*> AssetManager::FindAssets()
{
	AssetType assetType(typeid(T));

	return FindAssets(assetType);
}
