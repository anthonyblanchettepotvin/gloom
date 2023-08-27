#include "AssetRepository.h"

#include <cassert>
#include <stdexcept>

#include "../object/ObjectType.h"

#include "Asset.h"

#define ASSET_ALREADY_IN_REPOSITORY "Asset is already in the repository."

void AssetRepository::Insert(std::unique_ptr<Asset>& asset)
{
	assert(asset != nullptr);

	auto it = std::find(m_Assets.begin(), m_Assets.end(), asset);
	if (it != m_Assets.end())
	{
		throw std::runtime_error(ASSET_ALREADY_IN_REPOSITORY);
	}

	m_Assets.emplace_back(std::move(asset));
}

std::vector<Asset*> AssetRepository::GetAssets() const
{
	std::vector<Asset*> result;

	for (const auto& asset : m_Assets)
	{
		assert(asset != nullptr);

		result.push_back(asset.get());
	}

	return result;
}

std::vector<Asset*> AssetRepository::FindAssetsByObjectType(const ObjectType& objectType) const
{
	std::vector<Asset*> result;

	for (const auto& asset : m_Assets)
	{
		assert(asset != nullptr);

		if (asset->GetDescriptor().GetObjectType() == objectType)
		{
			result.push_back(asset.get());
		}
	}

	return result;
}

Asset* AssetRepository::FindAssetByObjectId(const ObjectID& objectId) const
{
	for (const auto& asset : m_Assets)
	{
		assert(asset != nullptr);
		assert(asset->GetObject() != nullptr);

		if (asset->GetObject()->GetId() == objectId)
		{
			return asset.get();
		}
	}

	return nullptr;
}
