#include "AssetManager.h"

#include "../object/ObjectType.h"

#include "Asset.h"
#include "AssetDescriptor.h"
#include "AssetFactory.h"
#include "AssetRegistry.h"
#include "AssetRepository.h"

AssetManager::AssetManager(AssetRegistry& assetRegistry, AssetRepository& assetRepository)
	: m_AssetRegistry(assetRegistry), m_AssetRepository(assetRepository)
{
}

void AssetManager::DefineAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory)
{
	m_AssetRegistry.DefineAsset(assetDescriptor, assetFactory);
}

Asset* AssetManager::CreateAssetWithObject(std::unique_ptr<Object>& object)
{
	const AssetRegistryEntry& assetRegistryEntry = m_AssetRegistry.FindEntry(object->GetObjectType());

	std::unique_ptr<Asset> asset = assetRegistryEntry.GetFactory().CreateWithObject(assetRegistryEntry.GetDescriptor(), object);
	Asset* assetPr = asset.get(); // Retrieve the raw pointer before the ownership is transferred to the repository.

	m_AssetRepository.Insert(asset);

	return assetPr;
}

Asset* AssetManager::CreateBlankAsset(const ObjectType& objectType)
{
	const AssetRegistryEntry& assetRegistryEntry = m_AssetRegistry.FindEntry(objectType);

	std::unique_ptr<Asset> blankAsset = assetRegistryEntry.GetFactory().CreateBlank(assetRegistryEntry.GetDescriptor());
	Asset* blankAssetPtr = blankAsset.get(); // Retrieve the raw pointer before the ownership is transferred to the repository.

	m_AssetRepository.Insert(blankAsset);

	return blankAssetPtr;
}

std::vector<Asset*> AssetManager::FindAssetsByObjectType(const ObjectType& objectType)
{
	return m_AssetRepository.FindAssetsByObjectType(objectType);
}
