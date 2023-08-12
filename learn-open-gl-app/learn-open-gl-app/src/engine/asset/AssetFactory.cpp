#include "AssetFactory.h"

#include <stdexcept>

#define NULL_OBJECT_ERROR "Object is null."
#define OBJECT_TYPES_MISMATCH_ERROR "Object's type doesn't match the asset descriptor's object type."

std::unique_ptr<Asset> AssetFactory::Create(const AssetDescriptor& assetDescriptor, std::unique_ptr<ObjectBase>& object) const
{
	Validate(assetDescriptor, object.get());

	return std::make_unique<Asset>(assetDescriptor, object);
}

std::unique_ptr<Asset> AssetFactory::CreateBlank(const AssetDescriptor& assetDescriptor) const
{
	std::unique_ptr<ObjectBase> blankObject = CreateBlankObject();

	Validate(assetDescriptor, blankObject.get());

	return std::make_unique<Asset>(assetDescriptor, blankObject);
}

void AssetFactory::Validate(const AssetDescriptor& assetDescriptor, ObjectBase* object) const
{
	if (!object)
	{
		throw std::invalid_argument(NULL_OBJECT_ERROR);
	}

	if (assetDescriptor.GetObjectType() != object->GetObjectType())
	{
		throw std::runtime_error(OBJECT_TYPES_MISMATCH_ERROR);
	}
}
