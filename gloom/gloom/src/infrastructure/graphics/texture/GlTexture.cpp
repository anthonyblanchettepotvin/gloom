#include "GlTexture.h"

#include <glad/glad.h>

#include "../../../engine/graphics/texture/Texture.h"

GlTexture::GlTexture(const Texture& texture)
	: m_Texture(texture)
{
	/* Here, we create a texture. */
	glGenTextures(1, &m_Id);
	/* We bind our texture so any subsequent texture commands will configure the currently
	bound texture. */
	glBindTexture(GL_TEXTURE_2D, m_Id);

	GLenum format = ChannelCountToFormat(m_Texture.GetChannelCount());

	/* We assign the loaded image's data to the currently bound texture. */
	glTexImage2D(GL_TEXTURE_2D, 0, format, (GLsizei)m_Texture.GetWidth(), (GLsizei)m_Texture.GetHeight(), 0, format, GL_UNSIGNED_BYTE, m_Texture.GetData());
	glGenerateMipmap(GL_TEXTURE_2D);

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

	m_Index = 0;
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
