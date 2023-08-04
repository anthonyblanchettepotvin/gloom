#pragma once

#include <string>

#include "../Asset.h"

class Texture : public Asset
{
public:
	Texture(size_t width, size_t height, size_t channelCount, unsigned char* data);
	virtual ~Texture() = default;

protected:
	size_t width;
	size_t height;
	size_t channelCount;

	unsigned char* data;
};
