#include "ShaderImporter.h"

#include <fstream>
#include <memory>
#include <sstream>

#include "../../../engine/EngineGlobals.h"
#include "../../../engine/graphics/engine/GraphicsEngine.h"
#include "../../../engine/graphics/shader/Shader.h"

ShaderImporter::ShaderImporter(AssetManager& assetManager)
	: AssetImporter(assetManager)
{
}

std::unique_ptr<Object> ShaderImporter::ImportObject(const std::string& assetName, const std::string& filePath)
{
    std::ifstream shaderFile;
    std::stringstream shaderFileBuf;

    try
    {
        shaderFile.open(filePath);
        shaderFileBuf << shaderFile.rdbuf();
        shaderFile.close();
    }
    catch (std::exception e)
    {
        std::stringstream ss;
        ss << "Could not import shader " << filePath << ".";
        gLogErrorMessage(ss.str());

        return nullptr;
    }

    return std::make_unique<Shader>(shaderFileBuf.str());
}
