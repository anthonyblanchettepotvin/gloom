#pragma once

#include "../AssetLoader.h"

#include "Texture.h"

class TextureLoader : public AssetLoader<Texture>
{
public:
	virtual Texture* Load(const std::string& filePath) override = 0;
};
