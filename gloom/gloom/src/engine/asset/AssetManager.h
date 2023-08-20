#pragma once

#include <memory>
#include <string>
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

	Asset* CreateAssetWithObject(const std::string& assetName, std::unique_ptr<Object>& object);
	Asset* CreateBlankAsset(const ObjectType& objectType, const std::string& assetName);

	std::vector<Asset*> GetAssets() const;
	std::vector<Asset*> FindAssetsByObjectType(const ObjectType& objectType) const;

	std::vector<AssetDescriptor> GetAssetDescriptors() const;

private:
	AssetRegistry& m_AssetRegistry;
	AssetRepository& m_AssetRepository;
};
