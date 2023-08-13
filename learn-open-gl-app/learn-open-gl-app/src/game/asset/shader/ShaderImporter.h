#pragma once

#include <string>

class Shader;

class ShaderImporter
{
public:
	virtual Shader* Import(const std::string& filePath) = 0;
};
