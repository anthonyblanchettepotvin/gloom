#include "GlCubemapLoader.h"

#include <iostream>

#include "../../../vendor/stbi/stb_image.h" // Image loading library by Sean Barrett.

#include "GlCubemap.h"
#include "GlCubemapTexture.h"

Cubemap* GlCubemapLoader::Load(const std::vector<std::string>& facesPath)
{
	stbi_set_flip_vertically_on_load(false);

	std::vector<CubemapTexture*> textures;

	for (size_t i = 0; i < facesPath.size(); i++)
	{
		std::string facePath = facesPath.at(i);

		int width, height, channelCount;
		unsigned char* data = stbi_load(facePath.c_str(), &width, &height, &channelCount, 0);
		if (data)
		{
			CubemapTexture* texture = new GlCubemapTexture(width, height, channelCount, data);

			textures.push_back(texture);
		}
		else
		{
			std::cout << "ERROR::CUBEMAP::LOADING::" << facePath << std::endl;
		}
	}
	return new GlCubemap(textures);
}
