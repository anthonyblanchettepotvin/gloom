#include "TextureImporter.h"

#include <sstream>

#include "../../../vendor/stbi/stb_image.h"

#include "../../../engine/EngineGlobals.h"
#include "../../../engine/graphics/texture/Texture.h"

TextureImporter::TextureImporter(AssetManager& assetManager)
	: AssetImporter(assetManager)
{
}

std::unique_ptr<Object> TextureImporter::ImportObject(const std::string& assetName, const std::string& filePath)
{
	/* OpenGL expects the 0.0 coordinate on the y-axis to be on the bottom side of the image,
	but images usually have 0.0 at the top of the y-axis. */
	stbi_set_flip_vertically_on_load(true);

	/* Here, we load an image from a file. */
	int width, height, channelCount;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channelCount, 0);
	if (!data)
	{
		std::stringstream ss;
		ss << "Could not import texture " << filePath << ".";
		gLogErrorMessage(ss.str());

		return nullptr;
	}

	return std::make_unique<Texture>(width, height, channelCount, data, true);
}
