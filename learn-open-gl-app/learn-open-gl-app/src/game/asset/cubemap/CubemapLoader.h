#pragma once

#include "../../../engine/graphics/cubemap/Cubemap.h"

#include "../AssetLoader.h"

class CubemapLoader : public AssetLoader<Cubemap>
{
public:
	Cubemap* Load(const std::string& filePath) override;
};
