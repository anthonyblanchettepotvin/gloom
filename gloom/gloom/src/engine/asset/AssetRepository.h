#pragma once

#include <memory>
#include <vector>

class Asset;
class ObjectID;
class ObjectType;

class AssetRepository
{
public:
	void Insert(std::unique_ptr<Asset>& asset);

	std::vector<Asset*> FindAssetsByObjectType(const ObjectType& objectType);
	std::vector<const Asset*> FindAssetsByObjectType(const ObjectType& objectType) const;

	Asset* FindAssetByObjectId(const ObjectID& objectId);
	const Asset* FindAssetByObjectId(const ObjectID& objectId) const;

	std::vector<Asset*> GetAssets();
	std::vector<const Asset*> GetAssets() const;

private:
	std::vector<std::unique_ptr<Asset>> m_Assets;

	template<class T, class Self>
	friend std::vector<T*> GetAssetsImpl(Self& self);

	template<class T, class Self>
	friend std::vector<T*> FindAssetsByObjectTypeImpl(Self& self, const ObjectType& objectType);

	template<class T, class Self>
	friend T* FindAssetByObjectIdImpl(Self& self, const ObjectID& objectId);
};
