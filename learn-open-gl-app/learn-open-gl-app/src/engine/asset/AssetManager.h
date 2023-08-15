#pragma once

#include <memory>
#include <vector>

class Asset;
class AssetDescriptor;
class AssetFactory;
class AssetRegistry;
class AssetRepository;
class Object;
class ObjectType;

class AssetManager
{
public:
	AssetManager(AssetRegistry& assetRegistry, AssetRepository& assetRepository);

	void DefineAsset(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory);

	Asset* CreateAssetWithObject(std::unique_ptr<Object>& object);
	Asset* CreateBlankAsset(const ObjectType& objectType);

	std::vector<Asset*> FindAssetsByObjectType(const ObjectType& objectType);

private:
	AssetRegistry& m_AssetRegistry;
	AssetRepository& m_AssetRepository;
};
