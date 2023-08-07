#pragma once

#include "../AssetLoader.h"

#include "Cubemap.h"

class CubemapLoader : public AssetLoader<Cubemap>
{
public:
	Cubemap* Load(const std::string& filePath) override;
};
