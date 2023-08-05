#include "GlCubemapLoader.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <experimental/filesystem>

#include "../../../vendor/stbi/stb_image.h" // Image loading library by Sean Barrett.

#include "GlCubemap.h"
#include "GlCubemapTexture.h"

Cubemap* GlCubemapLoader::Load(const std::string& filePath)
{
	// FIXME: This method is hackish and Cubemap has no validation on the number of textures.
	if (!std::experimental::filesystem::is_directory(filePath))
	{
		std::cout << "ERROR::CUBEMAP::LOADING::" << filePath << " is not a directory." << std::endl;
	}

	std::vector<std::string> facesPath;

	for (const auto& file : std::experimental::filesystem::directory_iterator(filePath))
	{
		if (file.path().extension() == ".jpg")
		{
			facesPath.push_back(file.path().generic_string());
		}
	}

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
