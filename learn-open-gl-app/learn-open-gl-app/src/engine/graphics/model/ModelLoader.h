#pragma once

#include <string>
#include <vector>

#include "Model.h"

#include "../texture/Texture.h"

class ModelLoader
{
public:
	virtual Model* Load(const std::string& path) = 0;
};
