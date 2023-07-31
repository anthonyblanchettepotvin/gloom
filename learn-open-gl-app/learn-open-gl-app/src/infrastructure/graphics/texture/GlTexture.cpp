#include "GlTexture.h"

#include "../shader/GlShader.h"

GlTexture::GlTexture(size_t width, size_t height, size_t channelCount, unsigned char* data)
	: Texture(width, height, channelCount, data), m_Index(0)
{
	/* Here, we create a texture. */
	glGenTextures(1, &m_Id);
	/* We bind our texture so any subsequent texture commands will configure the currently
	bound texture. */
	glBindTexture(GL_TEXTURE_2D, m_Id);

	GLenum format = ChannelCountToFormat(channelCount);

	/* We assign the loaded image's data to the currently bound texture. */
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// TODO: Should be configurable.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* We unbind our texture. */
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GlTexture::Use(unsigned int index)
{
	m_Index = index;

	glActiveTexture(GL_TEXTURE0 + m_Index);
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void GlTexture::Free()
{
	glActiveTexture(GL_TEXTURE0 + m_Index);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLenum GlTexture::ChannelCountToFormat(size_t channelCount) const
{
	switch (channelCount)
	{
	case 1:
		return GL_RED;
	case 2:
		return GL_RG;
	case 3:
		return GL_RGB;
	case 4:
		return GL_RGBA;
	default:
		return GL_RGB;
	}
}
