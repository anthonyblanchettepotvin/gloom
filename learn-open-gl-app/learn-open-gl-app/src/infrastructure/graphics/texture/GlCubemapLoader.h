#pragma once

#include "../../../game/asset/cubemap/CubemapLoader.h"

class GlCubemapLoader : public CubemapLoader
{
public:
	Cubemap* Load(const std::string& filePath) override;
};
