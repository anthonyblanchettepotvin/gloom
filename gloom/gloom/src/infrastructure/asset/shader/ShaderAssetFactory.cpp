#include "ShaderAssetFactory.h"

#include "../../../engine/graphics/shader/Shader.h"

std::unique_ptr<Object> ShaderAssetFactory::CreateBlankObject()
{
    return std::make_unique<Shader>();
}
