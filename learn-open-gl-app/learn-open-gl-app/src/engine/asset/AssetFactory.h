#pragma once

#include <memory>

class Asset;
class AssetDescriptor;
class Object;

class AssetFactory
{
public:
	std::unique_ptr<Asset> CreateWithObject(const AssetDescriptor& assetDescriptor, std::unique_ptr<Object>& object);
	std::unique_ptr<Asset> CreateBlank(const AssetDescriptor& assetDescriptor);

protected:
	virtual std::unique_ptr<Object> CreateBlankObject() = 0;
};
