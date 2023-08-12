#include "AssetRepository.h"

void AssetRepository::Insert(std::unique_ptr<Asset>& asset)
{
	auto it = std::find(m_Assets.begin(), m_Assets.end(), asset);
	if (it == m_Assets.end())
	{
		m_Assets.push_back(std::move(asset));
	}
	else
	{
		// TODO: Throw exception
	}
}

std::vector<Asset*> AssetRepository::FindAssetsByObjectType(const ObjectType& objectType) const
{
	std::vector<Asset*> result;

	for (const auto& asset : m_Assets)
	{
		if (asset && asset->GetAssetDescriptor().GetObjectType() == objectType)
		{
			result.push_back(asset.get());
		}
	}

	return result;
}
