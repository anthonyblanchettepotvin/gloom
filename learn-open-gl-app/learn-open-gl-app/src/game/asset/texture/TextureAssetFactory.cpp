#include "TextureAssetFactory.h"

#include "../../../engine/graphics/texture/Texture.h"

std::unique_ptr<ObjectBase> TextureAssetFactory::CreateBlankObject() const
{
	return std::make_unique<Texture>();
}
