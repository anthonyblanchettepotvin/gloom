#include "GlTextureLoader.h"

#include <iostream>

#include "../../../vendor/stbi/stb_image.h" // Image loading library by Sean Barrett.

#include "GlTexture.h"

Texture* GlTextureLoader::Load(const std::string& path)
{
	/* OpenGL expects the 0.0 coordinate on the y-axis to be on the bottom side of the image,
	but images usually have 0.0 at the top of the y-axis. */
	stbi_set_flip_vertically_on_load(true);

	Texture* texture = nullptr;

	/* Here, we load an image from a file. */
	int width, height, channelCount;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channelCount, 0);
	if (data)
	{
		texture = new GlTexture(width, height, channelCount, data);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::LOADING::" << path << std::endl;
	}

	return texture;
}
