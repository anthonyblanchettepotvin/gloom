#pragma once

#include <glad/glad.h>

#include "../../../game/asset/cubemap/Cubemap.h"

class GlCubemap
{
public:
	GlCubemap(const Cubemap& cubemap);

	void Use(unsigned int index);
	void Free();

private:
	const Cubemap& m_Cubemap;

	unsigned int m_Id;
	unsigned int m_Index = 0;

	GLenum ChannelCountToFormat(size_t channelCount) const;
};
