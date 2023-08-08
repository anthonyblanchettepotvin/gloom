#pragma once

#include <string>
#include <vector>

#include "../texture/Texture.h"

#include "../Asset.h"

class Cubemap : public Asset
{
public:
	Cubemap(const std::vector<Texture*>& textures);
	
	std::vector<Texture*> GetTextures() const { return textures; }

protected:
	std::vector<Texture*> textures;
};
