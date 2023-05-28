#pragma once

#include <glad/glad.h>

#include <string>

enum class TextureType {
	DIFFUSE,
	SPECULAR,
	UNKNOWN
};

class Texture
{
public:
	unsigned int id;

	Texture(size_t width, size_t height);
	Texture(const std::string& path, TextureType type, bool flipVerticallyOnLoad = true);

	TextureType GetType() { return type; };

private:
	TextureType type = TextureType::UNKNOWN;
};
