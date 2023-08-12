#include "AssetFactory.h"

std::unique_ptr<Asset> AssetFactory::Create(const AssetDescriptor& assetDescriptor, std::unique_ptr<Object>& object) const
{
	return std::make_unique<Asset>(assetDescriptor, object);
}

std::unique_ptr<Asset> AssetFactory::CreateBlank(const AssetDescriptor& assetDescriptor) const
{
	std::unique_ptr<Object> blankObject = CreateBlankObject();

	return std::make_unique<Asset>(assetDescriptor, blankObject);
}
