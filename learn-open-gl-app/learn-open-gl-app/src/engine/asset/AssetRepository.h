#pragma once

#include <memory>
#include <vector>

class Asset;
class ObjectType;

class AssetRepository
{
public:
	void Insert(std::unique_ptr<Asset>& asset);

	std::vector<Asset*> GetAssets() const;
	std::vector<Asset*> FindAssetsByObjectType(const ObjectType& objectType) const;

private:
	std::vector<std::unique_ptr<Asset>> m_Assets;
};
