#pragma once

#include <vector>
#include <string>

#include "Cubemap.h"

class CubemapLoader
{
public:
	virtual Cubemap* Load(const std::vector<std::string>& facesPath) = 0;
};
