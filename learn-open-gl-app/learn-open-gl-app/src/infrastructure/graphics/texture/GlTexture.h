#pragma once

#include <glad/glad.h>

#include "../../../game/asset/texture/Texture.h"

class GlTexture : public Texture
{
public:
	GlTexture(size_t width, size_t height, size_t channelCount, unsigned char* data);

	void Use(unsigned int index);
	void Free();

	unsigned int GetId() const { return m_Id; }

private:
	unsigned int m_Id;
	unsigned int m_Index;

	GLenum ChannelCountToFormat(size_t channelCount) const;
};
