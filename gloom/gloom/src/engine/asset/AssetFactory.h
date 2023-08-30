#pragma once

#include <memory>
#include <string>

class Asset;
class AssetDescriptor;
class Object;

class AssetFactory
{
public:
	std::unique_ptr<Asset> CreateBlank(const AssetDescriptor& assetDescriptor, const std::string& assetName);
	std::unique_ptr<Asset> CreateWithObject(const AssetDescriptor& assetDescriptor, const std::string& assetName, std::unique_ptr<Object>& object);

protected:
	virtual std::unique_ptr<Object> CreateBlankObject() = 0;
};
