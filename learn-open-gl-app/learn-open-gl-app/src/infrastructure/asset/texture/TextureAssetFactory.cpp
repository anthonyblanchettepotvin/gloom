#include "TextureAssetFactory.h"

#include "../../../engine/graphics/texture/Texture.h"

std::unique_ptr<ObjectBase> TextureAssetFactory::CreateBlankObject()
{
	return std::make_unique<Texture>();
}
