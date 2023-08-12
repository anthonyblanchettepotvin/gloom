#pragma once

#include <memory>
#include <vector>

#include "../object/ObjectType.h"

#include "Asset.h"

class AssetRepository
{
public:
	void Insert(std::unique_ptr<Asset>& asset);

	std::vector<Asset*> FindAssetsByObjectType(const ObjectType& objectType) const;

private:
	std::vector<std::unique_ptr<Asset>> m_Assets;
};
