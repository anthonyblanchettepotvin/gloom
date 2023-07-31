#pragma once

#include <string>

#include "Texture.h"

class TextureLoader
{
public:
	virtual Texture* Load(const std::string& path) = 0;
};
