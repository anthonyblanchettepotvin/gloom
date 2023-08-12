#pragma once

#include <string>
#include <vector>

class Cubemap;

class CubemapImporter
{
public:
	Cubemap* Load(const std::vector<std::string>& facesFilePath);
};
