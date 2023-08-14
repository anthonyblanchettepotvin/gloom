#pragma once

#include <string>

#include "../../../engine/asset/AssetImporter.h"

class GraphicsEngine;

class ShaderImporter : public AssetImporter<const std::string&>
{
public:
	ShaderImporter(AssetManager& assetManager, GraphicsEngine& graphicsEngine);

protected:
	std::unique_ptr<ObjectBase> ImportObject(const std::string& filePath) override;

private:
	GraphicsEngine& m_GraphicsEngine;
};
