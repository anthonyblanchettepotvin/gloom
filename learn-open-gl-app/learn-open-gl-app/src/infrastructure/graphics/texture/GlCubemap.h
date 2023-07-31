#pragma once

#include "../../../engine/graphics/texture/Cubemap.h"

class GlCubemap : public Cubemap
{
public:
	GlCubemap(const std::vector<CubemapTexture*>& textures);

	void Use(unsigned int index);
	void Free();

private:
	unsigned int m_Id;
	unsigned int m_Index;
};
