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

	GLenum glInternalFormat = TextureFormatToGlInternalFormat(m_Texture.GetFormat());
	GLenum glFormat = TextureFormatToGlFormat(m_Texture.GetFormat());
	GLenum glType = TextureFormatToGlType(m_Texture.GetFormat());

	/* We assign the loaded image's data to the currently bound texture. */
	glTexImage2D(GL_TEXTURE_2D, 0, glInternalFormat, (GLsizei)m_Texture.GetWidth(), (GLsizei)m_Texture.GetHeight(), 0, glFormat, glType, m_Texture.GetData());
	glGenerateMipmap(GL_TEXTURE_2D);

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

GLenum GlTexture::TextureFormatToGlInternalFormat(const TextureFormat& textureFormat) const
{
	switch (textureFormat)
	{
	case TextureFormat::R:
		return GL_RED;
	case TextureFormat::RG:
		return GL_RG;
	case TextureFormat::RGB:
		return GL_RGB;
	case TextureFormat::RGBA:
		return GL_RGBA;
	case TextureFormat::RGBA16F:
		return GL_RGBA16F;
	}
}

GLenum GlTexture::TextureFormatToGlFormat(const TextureFormat& textureFormat) const
{
	switch (textureFormat)
	{
	case TextureFormat::R:
		return GL_RED;
	case TextureFormat::RG:
		return GL_RG;
	case TextureFormat::RGB:
		return GL_RGB;
	case TextureFormat::RGBA:
		return GL_RGBA;
	case TextureFormat::RGBA16F:
		return GL_RGBA;
	}
}

GLenum GlTexture::TextureFormatToGlType(const TextureFormat& textureFormat) const
{
	switch (textureFormat)
	{
	case TextureFormat::R:
	case TextureFormat::RG:
	case TextureFormat::RGB:
	case TextureFormat::RGBA:
		return GL_UNSIGNED_BYTE;
	case TextureFormat::RGBA16F:
		return GL_HALF_FLOAT;
	}
}
