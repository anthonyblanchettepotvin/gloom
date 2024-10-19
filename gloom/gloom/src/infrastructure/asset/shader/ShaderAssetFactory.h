#pragma once

#include <memory>

#include "../../../engine/asset/AssetFactory.h"

class ShaderAssetFactory : public AssetFactory
{
protected:
	std::unique_ptr<Object> CreateBlankObject() override;
};
