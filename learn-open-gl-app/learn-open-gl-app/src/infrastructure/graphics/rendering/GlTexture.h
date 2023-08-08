#pragma once

#include <glad/glad.h>

#include "../../../game/asset/texture/Texture.h"

class GlTexture
{
public:
	GlTexture(const Texture& texture);

	void Use(unsigned int index);
	void Free();

	unsigned int GetId() const { return m_Id; }

private:
	const Texture& m_Texture;

	unsigned int m_Id;
	unsigned int m_Index = 0;

	GLenum ChannelCountToFormat(size_t channelCount) const;
};
