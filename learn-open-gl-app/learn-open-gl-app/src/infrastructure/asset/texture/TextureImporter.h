#pragma once

#include <string>

#include "../../../engine/asset/AssetImporter.h"

class TextureImporter : public AssetImporter<const std::string&>
{
public:
	TextureImporter(AssetManager& assetManager);

protected:
	std::unique_ptr<ObjectBase> ImportObject(const std::string& filePath) override;
};
