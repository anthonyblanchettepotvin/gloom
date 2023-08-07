#pragma once

#include "../AssetLoader.h"

#include "Texture.h"

class TextureLoader : public AssetLoader<Texture>
{
public:
	Texture* Load(const std::string& filePath) override;
};
