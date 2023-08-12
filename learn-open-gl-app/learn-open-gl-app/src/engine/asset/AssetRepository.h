#pragma once

#include <memory>
#include <vector>

#include "Asset.h"
#include "AssetDescriptor.h"

class AssetRepository
{
public:
	void Insert(std::unique_ptr<Asset>& asset);

	std::vector<Asset*> FindAssetsByType(const AssetType& assetType) const;

private:
	std::vector<std::unique_ptr<Asset>> m_Assets;
};
