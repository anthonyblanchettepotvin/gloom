#include "TextureLoader.h"

#include <iostream>

#include "../../../vendor/stbi/stb_image.h" // Image loading library by Sean Barrett.

Texture* TextureLoader::Load(const std::string& filePath)
{
	/* OpenGL expects the 0.0 coordinate on the y-axis to be on the bottom side of the image,
	but images usually have 0.0 at the top of the y-axis. */
	stbi_set_flip_vertically_on_load(true);

	Texture* texture = nullptr;

	/* Here, we load an image from a file. */
	int width, height, channelCount;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channelCount, 0);
	if (data)
	{
		texture = new Texture(width, height, channelCount, data);

		size_t pos = filePath.find_last_of('\\');
		std::string fileName = filePath.substr(pos, filePath.size() - pos);
		texture->SetName(fileName);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::LOADING::" << filePath << std::endl;
	}

	return texture;
}
