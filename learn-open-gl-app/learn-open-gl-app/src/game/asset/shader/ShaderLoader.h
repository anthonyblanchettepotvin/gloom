#pragma once

#include "../../../engine/graphics/shader/Shader.h"

class ShaderLoader
{
public:
	virtual Shader* Load(const std::string& filePath) = 0;
};
