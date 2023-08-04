#pragma once

#include "AssetLoader.h"
#include "TestAsset.h"

class TestAssetLoader : public AssetLoader<TestAsset>
{
public:
	TestAsset* Load(const std::string& filePath) override;
};
