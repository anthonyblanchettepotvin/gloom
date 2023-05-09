#pragma once

#include <glad/glad.h>

#include <string>

class Texture
{
public:
	unsigned int id;

	Texture(size_t width, size_t height);
	Texture(const std::string& path, const std::string& type, bool flipVerticallyOnLoad = true);

	std::string GetType() { return type; };
	std::string GetPath() { return path; };

private:
	std::string type;
	std::string path;
};
