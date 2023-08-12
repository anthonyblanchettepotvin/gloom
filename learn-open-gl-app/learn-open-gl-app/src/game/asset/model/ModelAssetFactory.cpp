#include "ModelAssetFactory.h"

#include "../../../engine/graphics/model/Model.h"

std::unique_ptr<ObjectBase> ModelAssetFactory::CreateBlankObject() const
{
	return std::make_unique<Model>();
}
