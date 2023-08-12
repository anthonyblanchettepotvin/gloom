#pragma once

#include <string>
#include <vector>

class Cubemap;

class CubemapLoader
{
public:
	Cubemap* Load(const std::vector<std::string>& facesFilePath);
};
