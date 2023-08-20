#pragma once

#include <string>
#include <vector>

#include "../../../engine/asset/AssetImporter.h"

class CubemapImporter : public AssetImporter<const std::vector<std::string>&>
{
public:
	CubemapImporter(AssetManager& assetManager);

protected:
	std::unique_ptr<Object> ImportObject(const std::string& assetName, const std::vector<std::string>& facesFilePath) override;
};
