#include "ModelAssetFactory.h"

#include "../../../engine/graphics/model/Model.h"

std::unique_ptr<ObjectBase> ModelAssetFactory::CreateBlankObject()
{
	return std::make_unique<Model>();
}
