#pragma once

#include <memory>
#include <vector>

class Asset;
class AssetDescriptor;
class AssetFactory;
class AssetRegistry;
class AssetRepository;
class ObjectBase;
class ObjectType;

class AssetManager
{
public:
	AssetManager(AssetRegistry& assetRegistry, AssetRepository& assetRepository);

	void DefineAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory);

	Asset* CreateAssetWithObject(std::unique_ptr<ObjectBase>& object);

	template<class T>
	Asset* CreateBlankAsset();
	Asset* CreateBlankAsset(const ObjectType& objectType);

	template<class T>
	std::vector<Asset*> FindAssetsByObjectType();
	std::vector<Asset*> FindAssetsByObjectType(const ObjectType& objectType);

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
inline std::vector<Asset*> AssetManager::FindAssetsByObjectType()
{
	ObjectType objectType(typeid(T));

	return FindAssetsByObjectType(objectType);
}
