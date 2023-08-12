#pragma once

#include <string>

class Shader;

class ShaderImporter
{
public:
	virtual Shader* Load(const std::string& filePath) = 0;
};
