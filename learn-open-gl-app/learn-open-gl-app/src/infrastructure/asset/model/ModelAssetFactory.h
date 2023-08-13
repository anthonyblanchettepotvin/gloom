#pragma once

#include <memory>

#include "../../../engine/asset/AssetFactory.h"

class ModelAssetFactory : public AssetFactory
{
protected:
	std::unique_ptr<ObjectBase> CreateBlankObject() override;
};
