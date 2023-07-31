#pragma once

#include "../../../engine/graphics/texture/CubemapLoader.h"

class GlCubemapLoader : public CubemapLoader
{
public:
	Cubemap* Load(const std::vector<std::string>& facesPath);
};
