#pragma once

#include "../../../engine/graphics/texture/Texture.h"

#include "../AssetLoader.h"

class TextureLoader : public AssetLoader<Texture>
{
public:
	Texture* Load(const std::string& filePath) override;
};
