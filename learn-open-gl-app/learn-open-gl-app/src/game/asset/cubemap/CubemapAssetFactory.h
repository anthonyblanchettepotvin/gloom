#pragma once

#include <memory>

#include "../../../engine/asset/AssetFactory.h"

class CubemapAssetFactory : public AssetFactory
{
protected:
	std::unique_ptr<ObjectBase> CreateBlankObject() const override;
};
