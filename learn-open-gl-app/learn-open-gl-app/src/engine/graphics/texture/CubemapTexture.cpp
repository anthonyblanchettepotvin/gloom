#include "CubemapTexture.h"

CubemapTexture::CubemapTexture(size_t width, size_t height, size_t channelCount, unsigned char* data)
	: Texture(width, height, channelCount, data)
{
}
