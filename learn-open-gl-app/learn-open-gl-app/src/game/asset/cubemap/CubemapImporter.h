#pragma once

#include <string>
#include <vector>

#include "../../../engine/asset/AssetImporter.h"

class Cubemap;

class CubemapImporter : public AssetImporter<const std::vector<std::string>&>
{
public:
	CubemapImporter(AssetManager& assetManager);

protected:
	std::unique_ptr<ObjectBase> ImportObject(const std::vector<std::string>& facesFilePath) override;
};
