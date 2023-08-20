#include "CubemapImporter.h"

#include "../../../vendor/stbi/stb_image.h" // Image loading library by Sean Barrett.

#include "../../../engine/graphics/cubemap/Cubemap.h"

CubemapImporter::CubemapImporter(AssetManager& assetManager)
	: AssetImporter(assetManager)
{
}

std::unique_ptr<Object> CubemapImporter::ImportObject(const std::string& assetName, const std::vector<std::string>& facesFilePath)
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
			Texture* texture = new Texture(width, height, channelCount, data, false);

			textures.push_back(texture);
		}
		else
		{
			// TODO: Log error
		}
	}

	return std::make_unique<Cubemap>(textures);
}
