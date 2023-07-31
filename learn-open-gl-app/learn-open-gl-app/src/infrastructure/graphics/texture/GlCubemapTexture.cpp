#include "GlCubemapTexture.h"

GlCubemapTexture::GlCubemapTexture(size_t width, size_t height, size_t channelCount, unsigned char* data)
	: CubemapTexture(width, height, channelCount, data)
{
}

void GlCubemapTexture::Register(unsigned int index)
{
	GLenum format = ChannelCountToFormat(channelCount);

	/* That's a neat little trick here. OpenGL define the six targets (one for each face of the cubemap)
	one after the other in order. We can then iterate over an array and simply offset the
	first target by the iteration to get the value of the current target. */
	/* You can get the list of all the cubemap targets here https://learnopengl.com/Advanced-OpenGL/Cubemaps. */
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
}

GLenum GlCubemapTexture::ChannelCountToFormat(size_t channelCount) const
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
