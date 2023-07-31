#include "Texture.h"

Texture::Texture(size_t width, size_t height, size_t channelCount, unsigned char* data)
	: width(width), height(height), channelCount(channelCount), data(data)
{
}
