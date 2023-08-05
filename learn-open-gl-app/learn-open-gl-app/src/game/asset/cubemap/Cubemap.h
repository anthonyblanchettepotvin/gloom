#pragma once

#include <string>
#include <vector>

#include "../Asset.h"

#include "CubemapTexture.h"

class Cubemap : public Asset
{
public:
	Cubemap(const std::vector<CubemapTexture*>& textures);
	virtual ~Cubemap() = default;

protected:
	std::vector<CubemapTexture*> textures;
};
