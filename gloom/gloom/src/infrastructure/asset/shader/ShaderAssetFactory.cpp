#include "ShaderAssetFactory.h"

#include "../../../engine/graphics/engine/GraphicsEngine.h"
#include "../../../engine/graphics/shader/Shader.h"

ShaderAssetFactory::ShaderAssetFactory(GraphicsEngine& graphicsEngine)
    : m_GraphicsEngine(graphicsEngine)
{
}

std::unique_ptr<Object> ShaderAssetFactory::CreateBlankObject()
{
    return m_GraphicsEngine.CreateShader();
}
