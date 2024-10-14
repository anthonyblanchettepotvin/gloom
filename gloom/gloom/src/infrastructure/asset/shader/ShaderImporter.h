#pragma once

#include <string>

#include "../../../engine/asset/AssetImporter.h"

class GraphicsEngine;

class ShaderImporter : public AssetImporter<const std::string&>
{
public:
	ShaderImporter(AssetManager& assetManager);

protected:
	std::unique_ptr<Object> ImportObject(const std::string& assetName, const std::string& filePath) override;
};
