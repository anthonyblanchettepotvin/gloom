#include "AssetRepository.h"

#include <stdexcept>

#define ASSET_ALREADY_IN_REPOSITORY "Asset is already in the repository."

void AssetRepository::Insert(std::unique_ptr<Asset>& asset)
{
	auto it = std::find(m_Assets.begin(), m_Assets.end(), asset);
	if (it == m_Assets.end())
	{
		m_Assets.push_back(std::move(asset));
	}
	else
	{
		throw std::runtime_error(ASSET_ALREADY_IN_REPOSITORY);
	}
}

std::vector<Asset*> AssetRepository::FindAssetsByObjectType(const ObjectType& objectType) const
{
	std::vector<Asset*> result;

	for (const auto& asset : m_Assets)
	{
		if (asset && asset->GetDescriptor().GetObjectType() == objectType)
		{
			result.push_back(asset.get());
		}
	}

	return result;
}
