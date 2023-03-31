#pragma once

#include <glad/glad.h>

#include <string>

class Texture
{
public:
	unsigned int id;

	Texture(const std::string& path, bool flipVerticallyOnLoad = true);
};
