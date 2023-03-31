#pragma once

#include <glad/glad.h>

#include <string>

class Texture
{
public:
	unsigned int id;
	std::string type;

	Texture(const std::string& path, const std::string& type, bool flipVerticallyOnLoad = true);
};
