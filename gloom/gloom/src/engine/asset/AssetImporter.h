#pragma once

#include <memory>
#include <string>

#include "../object/Object.h"

#include "AssetManager.h"

class Asset;
class AssetDescriptor;
class Object;
class ObjectType;

template<class ...Args>
class AssetImporter
{
public:
	AssetImporter(AssetManager& assetManager);

	Asset* Import(const std::string& assetName, Args... args);

protected:
	virtual std::unique_ptr<Object> ImportObject(const std::string& assetName, Args... args) = 0;

	AssetManager& m_AssetManager;
};

template<class ...Args>
inline AssetImporter<Args...>::AssetImporter(AssetManager& assetManager)
	: m_AssetManager(assetManager)
{
}

template<class ...Args>
inline Asset* AssetImporter<Args...>::Import(const std::string& assetName, Args... args)
{
	std::unique_ptr<Object> importedObject = ImportObject(assetName, args...);

	return m_AssetManager.CreateAssetWithObject(assetName, importedObject);
}
