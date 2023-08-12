#pragma once

#include <string>

class Texture;

class TextureImporter
{
public:
	Texture* Load(const std::string& filePath);
};
