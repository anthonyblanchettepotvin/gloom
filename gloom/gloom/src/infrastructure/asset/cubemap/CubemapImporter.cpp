#include "CubemapImporter.h"

#include <memory>
#include <sstream>

#include "../../../vendor/stbi/stb_image.h"

#include "../../../engine/EngineGlobals.h"
#include "../../../engine/graphics/cubemap/Cubemap.h"
#include "../../../engine/graphics/texture/Texture.h"

CubemapImporter::CubemapImporter(AssetManager& assetManager)
	: AssetImporter(assetManager)
{
}

std::unique_ptr<Object> CubemapImporter::ImportObject(const std::string& assetName, const std::vector<std::string>& facesFilePath)
{
	stbi_set_flip_vertically_on_load(false);

	std::vector<std::unique_ptr<Texture>> textures;

	for (size_t i = 0; i < facesFilePath.size(); i++)
	{
		std::string faceFilePath = facesFilePath.at(i);

		int width, height, channelCount;
		unsigned char* data = stbi_load(faceFilePath.c_str(), &width, &height, &channelCount, 0);
		if (!data)
		{
			std::stringstream ss;
			ss << "Could not import cubemap texture " << faceFilePath << ".";
			gLogErrorMessage(ss.str());

			return nullptr;
		}

		textures.emplace_back(std::make_unique<Texture>(width, height, channelCount, data, false));
	}

	return std::make_unique<Cubemap>(textures);
}
