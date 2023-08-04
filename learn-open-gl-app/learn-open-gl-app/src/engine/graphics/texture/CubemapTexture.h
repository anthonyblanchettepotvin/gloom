#pragma once

#include "../../../game/asset/texture/Texture.h"

class CubemapTexture : public Texture
{
public:
	CubemapTexture(size_t width, size_t height, size_t channelCount, unsigned char* data);
};
