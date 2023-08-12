#include "AssetManager.h"

AssetManager::AssetManager(AssetRegistry& assetRegistry, AssetRepository& assetRepository)
	: m_AssetRegistry(assetRegistry), m_AssetRepository(assetRepository)
{
}

void AssetManager::RegisterAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory)
{
	m_AssetRegistry.RegisterAsset(assetDescriptor, assetFactory);
}

Asset* AssetManager::CreateBlankAsset(const AssetType& assetType)
{
	const AssetRegistryEntry& assetRegistryEntry = m_AssetRegistry.FindEntry(assetType);

	std::unique_ptr<Asset> blankAsset = assetRegistryEntry.GetFactory().CreateBlank(assetRegistryEntry.GetDescriptor());
	Asset* blankAssetPtr = blankAsset.get(); // Retrieve the raw pointer before the ownership is transferred to the repository.

	m_AssetRepository.Insert(blankAsset);

	return blankAssetPtr;
}

std::vector<Asset*> AssetManager::FindAssets(const AssetType& assetType)
{
	return m_AssetRepository.FindAssetsByType(assetType);
}
