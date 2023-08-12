#pragma once

#include <memory>

class Asset;
class AssetDescriptor;
class ObjectBase;

class AssetFactory
{
public:
	std::unique_ptr<Asset> Create(const AssetDescriptor& assetDescriptor, std::unique_ptr<ObjectBase>& object) const;
	std::unique_ptr<Asset> CreateBlank(const AssetDescriptor& assetDescriptor) const;

protected:
	virtual std::unique_ptr<ObjectBase> CreateBlankObject() const = 0;

private:
	void Validate(const AssetDescriptor& assetDescriptor, ObjectBase* object) const;
};
