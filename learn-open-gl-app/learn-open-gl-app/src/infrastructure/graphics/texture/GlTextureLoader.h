#pragma once

#include "../../../engine/graphics/texture/TextureLoader.h"

class GlTextureLoader : public TextureLoader
{
public:
	Texture* Load(const std::string& path) override;
};
