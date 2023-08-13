#pragma once

#include <string>
#include <vector>

class Cubemap;

class CubemapImporter
{
public:
	Cubemap* Import(const std::vector<std::string>& facesFilePath);
};
