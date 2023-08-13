#pragma once

#include <string>

class Texture;

class TextureImporter
{
public:
	Texture* Import(const std::string& filePath);
};
