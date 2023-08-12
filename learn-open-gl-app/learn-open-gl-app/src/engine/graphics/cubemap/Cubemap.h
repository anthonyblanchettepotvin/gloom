#pragma once

#include <string>
#include <vector>

#include "../../object/Object.h"

#include "../texture/Texture.h"

class Cubemap : public Object<Cubemap>
{
public:
	Cubemap(const std::vector<Texture*>& textures);
	
	std::vector<Texture*> GetTextures() const { return textures; }

protected:
	std::vector<Texture*> textures;
};
