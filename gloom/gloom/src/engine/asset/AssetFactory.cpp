#include "AssetFactory.h"

#include <cassert>

#include "../object/Object.h"

#include "Asset.h"
#include "AssetDescriptor.h"

std::unique_ptr<Asset> AssetFactory::CreateBlank(const AssetDescriptor& assetDescriptor, const std::string& assetName)
{
	std::unique_ptr<Object> blankObject = CreateBlankObject();

	// TODO: Modify this if needed when assertion vs. exception conventions are defined.
	assert(blankObject != nullptr);
	assert(blankObject->GetObjectType() == assetDescriptor.GetObjectType());

	return std::make_unique<Asset>(assetDescriptor, assetName, blankObject);
}

std::unique_ptr<Asset> AssetFactory::CreateWithObject(const AssetDescriptor& assetDescriptor, const std::string& assetName, std::unique_ptr<Object>& object)
{
	// TODO: Modify this if needed when assertion vs. exception conventions are defined.
	assert(object != nullptr);
	assert(object->GetObjectType() == assetDescriptor.GetObjectType());

	return std::make_unique<Asset>(assetDescriptor, assetName, object);
}
