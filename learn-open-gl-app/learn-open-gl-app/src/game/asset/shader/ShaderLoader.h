#pragma once

#include <string>

class Shader;

class ShaderLoader
{
public:
	virtual Shader* Load(const std::string& filePath) = 0;
};
