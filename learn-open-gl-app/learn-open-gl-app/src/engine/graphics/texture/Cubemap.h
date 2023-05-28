#pragma once

#include <string>
#include <vector>

class Cubemap
{
public:
	unsigned int id;

	Cubemap(const std::vector<std::string>& facesPath, bool flipVerticallyOnLoad = true);
};
