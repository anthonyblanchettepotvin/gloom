#pragma once

#include <string>
#include <vector>

#include "CubemapTexture.h"

class Cubemap
{
public:
	Cubemap(const std::vector<CubemapTexture*>& textures);
	virtual ~Cubemap() = default;

protected:
	std::vector<CubemapTexture*> textures;
};
