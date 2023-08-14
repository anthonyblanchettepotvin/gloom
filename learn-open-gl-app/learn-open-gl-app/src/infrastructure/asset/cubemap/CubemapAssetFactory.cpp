#include "CubemapAssetFactory.h"

#include "../../../engine/graphics/cubemap/Cubemap.h"

std::unique_ptr<Object> CubemapAssetFactory::CreateBlankObject()
{
    return std::make_unique<Cubemap>();
}
