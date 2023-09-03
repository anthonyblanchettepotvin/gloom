#pragma once

#include <memory>
#include <vector>

#include "../../object/Object.h"

#include "../texture/Texture.h"

class Cubemap : public Object
{
public:
	Cubemap() = default;
	Cubemap(std::vector<std::unique_ptr<Texture>>& textures);
	
	std::vector<Texture*> GetTextures();
	std::vector<const Texture*> GetTextures() const;

protected:
	std::vector<std::unique_ptr<Texture>> m_Textures;

	template<class T, class Self>
	friend std::vector<T*> GetTexturesImpl(Self& self);
};
