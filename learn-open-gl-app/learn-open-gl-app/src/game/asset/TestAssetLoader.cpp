#include "TestAssetLoader.h"

TestAsset* TestAssetLoader::Load(const std::string& filePath)
{
    return new TestAsset();
}
