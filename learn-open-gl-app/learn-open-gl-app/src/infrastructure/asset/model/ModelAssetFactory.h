#pragma once

#include <memory>

#include "../../../engine/asset/AssetFactory.h"

class ModelAssetFactory : public AssetFactory
{
protected:
	std::unique_ptr<Object> CreateBlankObject() override;
};
