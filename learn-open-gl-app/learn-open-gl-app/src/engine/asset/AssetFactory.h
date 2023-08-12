#pragma once

#include <memory>

#include "../object/Object.h"

#include "Asset.h"
#include "AssetDescriptor.h"

class AssetFactory
{
public:
	std::unique_ptr<Asset> Create(const AssetDescriptor& assetDescriptor, std::unique_ptr<Object>& object) const;
	std::unique_ptr<Asset> CreateBlank(const AssetDescriptor& assetDescriptor) const;

protected:
	virtual std::unique_ptr<Object> CreateBlankObject() const = 0;
};
