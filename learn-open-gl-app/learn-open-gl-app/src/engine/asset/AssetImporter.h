#pragma once

#include <cassert>
#include <memory>

#include "../object/Object.h"

#include "AssetManager.h"

class Asset;
class AssetDescriptor;
class AssetManager;
class ObjectBase;
class ObjectType;

template<class ...Args>
class AssetImporter
{
public:
	AssetImporter(AssetManager& assetManager);

	Asset* Import(Args... args);

protected:
	virtual std::unique_ptr<ObjectBase> ImportObject(Args... args) = 0;

	AssetManager& m_AssetManager;
};

template<class ...Args>
inline AssetImporter<Args...>::AssetImporter(AssetManager& assetManager)
	: m_AssetManager(assetManager)
{
}

template<class ...Args>
inline Asset* AssetImporter<Args...>::Import(Args... args)
{
	std::unique_ptr<ObjectBase> importedObject = ImportObject(args...);

	return m_AssetManager.CreateAssetWithObject(importedObject);
}
