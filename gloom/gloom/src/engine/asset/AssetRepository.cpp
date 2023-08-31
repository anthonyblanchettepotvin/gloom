#include "AssetRepository.h"

#include <cassert>
#include <stdexcept>

#include "../object/Object.h"
#include "../object/ObjectType.h"

#include "Asset.h"

#define ASSET_ALREADY_IN_REPOSITORY "Asset is already in the repository."

void AssetRepository::Insert(std::unique_ptr<Asset>& asset)
{
	assert(asset != nullptr); // FIXME: Should throw an exception

	auto it = std::find(m_Assets.begin(), m_Assets.end(), asset);
	if (it != m_Assets.end())
	{
		throw std::runtime_error(ASSET_ALREADY_IN_REPOSITORY);
	}

	m_Assets.emplace_back(std::move(asset));
}

template<class T, class Self>
std::vector<T*> FindAssetsByObjectTypeImpl(Self& self, const ObjectType& objectType)
{
	std::vector<T*> result;

	for (const auto& asset : self.m_Assets)
	{
		assert(asset != nullptr);

		if (asset->GetDescriptor().GetObjectType() == objectType)
		{
			result.push_back(asset.get());
		}
	}

	return result;
}

std::vector<Asset*> AssetRepository::FindAssetsByObjectType(const ObjectType& objectType)
{
	return FindAssetsByObjectTypeImpl<Asset>(*this, objectType);
}

std::vector<const Asset*> AssetRepository::FindAssetsByObjectType(const ObjectType& objectType) const
{
	return FindAssetsByObjectTypeImpl<const Asset>(*this, objectType);
}

template<class T, class Self>
T* FindAssetByObjectIdImpl(Self& self, const ObjectID& objectId)
{
	for (const auto& asset : self.m_Assets)
	{
		assert(asset != nullptr);
		/* FIXME: It's totally valid that the object can be nullptr (if it's not loaded).
		Although, we still want a single source of truth for the object's ID. */
		assert(asset->GetObject() != nullptr);

		if (asset->GetObject()->GetId() == objectId)
		{
			return asset.get();
		}
	}

	return nullptr;
}

Asset* AssetRepository::FindAssetByObjectId(const ObjectID& objectId)
{
	return FindAssetByObjectIdImpl<Asset>(*this, objectId);
}

const Asset* AssetRepository::FindAssetByObjectId(const ObjectID& objectId) const
{
	return FindAssetByObjectIdImpl<const Asset>(*this, objectId);
}

template<class T, class Self>
std::vector<T*> GetAssetsImpl(Self& self)
{
	std::vector<T*> result;

	for (const auto& asset : self.m_Assets)
	{
		assert(asset != nullptr);

		result.push_back(asset.get());
	}

	return result;
}

std::vector<Asset*> AssetRepository::GetAssets()
{
	return GetAssetsImpl<Asset>(*this);
}

std::vector<const Asset*> AssetRepository::GetAssets() const
{
	return GetAssetsImpl<const Asset>(*this);
}
