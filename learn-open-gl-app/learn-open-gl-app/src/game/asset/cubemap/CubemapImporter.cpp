#include "CubemapImporter.h"

#include <iostream>

#include "../../../vendor/stbi/stb_image.h" // Image loading library by Sean Barrett.

#include "../../../engine/graphics/cubemap/Cubemap.h"

Cubemap* CubemapImporter::Import(const std::vector<std::string>& facesFilePath)
{
	stbi_set_flip_vertically_on_load(false);

	std::vector<Texture*> textures;

	for (size_t i = 0; i < facesFilePath.size(); i++)
	{
		std::string facePath = facesFilePath.at(i);

		int width, height, channelCount;
		unsigned char* data = stbi_load(facePath.c_str(), &width, &height, &channelCount, 0);
		if (data)
		{
			Texture* texture = new Texture(width, height, channelCount, data);

			textures.push_back(texture);
		}
		else
		{
			std::cout << "ERROR::CUBEMAP::IMPORTING::" << facePath << std::endl;
		}
	}

	return new Cubemap(textures);
}
