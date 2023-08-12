#pragma once

#include <string>

class Texture;

class TextureLoader
{
public:
	Texture* Load(const std::string& filePath);
};
