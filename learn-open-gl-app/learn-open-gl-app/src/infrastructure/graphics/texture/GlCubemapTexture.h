#pragma once

#include "glad/glad.h"

#include "../../../game/asset/cubemap/CubemapTexture.h"

class GlCubemapTexture : public CubemapTexture
{
public:
	GlCubemapTexture(size_t width, size_t height, size_t channelCount, unsigned char* data);

	void Register(unsigned int index);

private:
	GLenum ChannelCountToFormat(size_t channelCount) const;
};
