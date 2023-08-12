#pragma once

#include <memory>
#include <vector>

class Asset;
class AssetDescriptor;
class AssetFactory;
class AssetRegistry;
class AssetRepository;
class ObjectType;

class AssetManager
{
public:
	AssetManager(AssetRegistry& assetRegistry, AssetRepository& assetRepository);

	void RegisterAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory);

	template<class T>
	Asset* CreateBlankAsset();
	Asset* CreateBlankAsset(const ObjectType& objectType);

	template<class T>
	std::vector<Asset*> FindAssets();
	std::vector<Asset*> FindAssets(const ObjectType& objectType);

private:
	AssetRegistry& m_AssetRegistry;
	AssetRepository& m_AssetRepository;
};

template<class T>
inline Asset* AssetManager::CreateBlankAsset()
{
	ObjectType objectType(typeid(T));

	return CreateBlankAsset(objectType);
}

template<class T>
inline std::vector<Asset*> AssetManager::FindAssets()
{
	ObjectType objectType(typeid(T));

	return FindAssets(objectType);
}
