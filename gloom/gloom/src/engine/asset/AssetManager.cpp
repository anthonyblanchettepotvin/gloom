#include "AssetManager.h"

#include "../object/Object.h"
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

Asset* AssetManager::CreateBlankAsset(const ObjectType& objectType, const std::string& assetName)
{
	AssetRegistryEntry& assetRegistryEntry = m_AssetRegistry.FindEntry(objectType);

	std::unique_ptr<Asset> blankAsset = assetRegistryEntry.GetFactory().CreateBlank(assetRegistryEntry.GetDescriptor(), assetName);
	Asset* blankAssetPtr = blankAsset.get(); // Retrieve the raw pointer before the ownership is transferred to the repository.

	m_AssetRepository.Insert(blankAsset);

	return blankAssetPtr;
}

Asset* AssetManager::CreateAssetWithObject(const std::string& assetName, std::unique_ptr<Object>& object)
{
	AssetRegistryEntry& assetRegistryEntry = m_AssetRegistry.FindEntry(object->GetObjectType());

	std::unique_ptr<Asset> asset = assetRegistryEntry.GetFactory().CreateWithObject(assetRegistryEntry.GetDescriptor(), assetName, object);
	Asset* assetPtr = asset.get(); // Retrieve the raw pointer before the ownership is transferred to the repository.

	m_AssetRepository.Insert(asset);

	return assetPtr;
}

std::vector<Asset*> AssetManager::FindAssetsByObjectType(const ObjectType& objectType)
{
	return m_AssetRepository.FindAssetsByObjectType(objectType);
}

std::vector<const Asset*> AssetManager::FindAssetsByObjectType(const ObjectType& objectType) const
{
	return const_cast<const AssetRepository&>(m_AssetRepository).FindAssetsByObjectType(objectType);
}

Asset* AssetManager::FindAssetByObjectId(const ObjectID& objectId)
{
	return m_AssetRepository.FindAssetByObjectId(objectId);
}

const Asset* AssetManager::FindAssetByObjectId(const ObjectID& objectId) const
{
	return const_cast<const AssetRepository&>(m_AssetRepository).FindAssetByObjectId(objectId);
}

std::vector<AssetDescriptor> AssetManager::GetAssetDescriptors() const
{
	return m_AssetRegistry.GetAssetDescriptors();
}

std::vector<Asset*> AssetManager::GetAssets()
{
	return m_AssetRepository.GetAssets();
}

std::vector<const Asset*> AssetManager::GetAssets() const
{
	return const_cast<const AssetRepository&>(m_AssetRepository).GetAssets();
}
