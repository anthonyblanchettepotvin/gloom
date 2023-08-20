#include "TextureAssetFactory.h"

#include "../../../engine/graphics/texture/Texture.h"

std::unique_ptr<Object> TextureAssetFactory::CreateBlankObject()
{
	return std::make_unique<Texture>();
}
