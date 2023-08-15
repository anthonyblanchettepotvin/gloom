#pragma once

#include "../../../engine/asset/AssetFactory.h"

class MaterialAssetFactory : public AssetFactory
{
protected:
	std::unique_ptr<Object> CreateBlankObject() override;
};
