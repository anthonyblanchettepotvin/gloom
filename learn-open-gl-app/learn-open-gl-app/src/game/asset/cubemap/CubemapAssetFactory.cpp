#include "CubemapAssetFactory.h"

#include "../../../engine/graphics/cubemap/Cubemap.h"

std::unique_ptr<ObjectBase> CubemapAssetFactory::CreateBlankObject() const
{
    return std::make_unique<Cubemap>();
}
