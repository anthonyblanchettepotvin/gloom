#pragma once

#include <string>

#include "Model.h"

class ModelLoader
{
public:
	virtual Model* Load(const std::string& path) = 0;
};
