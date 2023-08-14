#include "ShaderImporter.h"

#include "../../../engine/graphics/engine/GraphicsEngine.h"
#include "../../../engine/graphics/shader/Shader.h"

ShaderImporter::ShaderImporter(AssetManager& assetManager, GraphicsEngine& graphicsEngine)
	: AssetImporter(assetManager), m_GraphicsEngine(graphicsEngine)
{
}

std::unique_ptr<ObjectBase> ShaderImporter::ImportObject(const std::string& filePath)
{
	return m_GraphicsEngine.ImportShader(filePath);
}
