#pragma once

#include <string>

#include "Shader.h"

class ShaderLoader
{
public:
	virtual Shader* Load(const std::string& path) = 0;
};
