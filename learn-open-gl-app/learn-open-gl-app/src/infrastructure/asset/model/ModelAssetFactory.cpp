#include "ModelAssetFactory.h"

#include "../../../engine/graphics/model/Model.h"

std::unique_ptr<Object> ModelAssetFactory::CreateBlankObject()
{
	return std::make_unique<Model>();
}
