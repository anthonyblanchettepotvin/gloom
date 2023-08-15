#include "MaterialAssetFactory.h"

#include "../../../engine/graphics/material/Material.h"

std::unique_ptr<Object> MaterialAssetFactory::CreateBlankObject()
{
    return std::make_unique<Material>();
}
