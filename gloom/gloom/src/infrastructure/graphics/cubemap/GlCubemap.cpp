#include "GlCubemap.h"

#include "../../../engine/graphics/texture/Texture.h"

GlCubemap::GlCubemap(const Cubemap& cubemap)
	: m_Cubemap(cubemap)
{
	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);

	for (size_t i = 0; i < cubemap.GetTextures().size(); i++)
	{
		const Texture* texture = cubemap.GetTextures()[i];

		GLenum format = ChannelCountToFormat(texture->GetChannelCount());

		/* That's a neat little trick here. OpenGL define the six targets (one for each face of the cubemap)
		one after the other in order. We can then iterate over an array and simply offset the
		first target by the iteration to get the value of the current target. */
		/* You can get the list of all the cubemap targets here https://learnopengl.com/Advanced-OpenGL/Cubemaps. */
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + (GLsizei)i, 0, format, (GLsizei)texture->GetWidth(), (GLsizei)texture->GetHeight(), 0, format, GL_UNSIGNED_BYTE, texture->GetData());
	}

	// TODO: Should be configurable.
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void GlCubemap::Use(unsigned int index)
{
	m_Index = index;

	glActiveTexture(GL_TEXTURE0 + m_Index);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);
}

void GlCubemap::Free()
{
	glActiveTexture(GL_TEXTURE0 + m_Index);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLenum GlCubemap::ChannelCountToFormat(size_t channelCount) const
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
