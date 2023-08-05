#pragma once

#include "../../../game/asset/texture/TextureLoader.h"

class GlTextureLoader : public TextureLoader
{
public:
	Texture* Load(const std::string& filePath) override;
};
