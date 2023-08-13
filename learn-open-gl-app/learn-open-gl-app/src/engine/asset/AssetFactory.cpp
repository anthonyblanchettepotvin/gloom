#include "AssetFactory.h"

#include <cassert>

#include "../object/Object.h"

#include "Asset.h"
#include "AssetDescriptor.h"

std::unique_ptr<Asset> AssetFactory::CreateWithObject(const AssetDescriptor& assetDescriptor, std::unique_ptr<ObjectBase>& object)
{
	assert(object != nullptr);
	assert(object->GetObjectType() == assetDescriptor.GetObjectType());

	return std::make_unique<Asset>(assetDescriptor, object);
}

std::unique_ptr<Asset> AssetFactory::CreateBlank(const AssetDescriptor& assetDescriptor)
{
	std::unique_ptr<ObjectBase> blankObject = CreateBlankObject();

	assert(blankObject != nullptr);
	assert(blankObject->GetObjectType() == assetDescriptor.GetObjectType());

	return std::make_unique<Asset>(assetDescriptor, blankObject);
}
