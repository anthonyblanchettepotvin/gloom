#pragma once

#include "../AssetLoader.h"

#include "Shader.h"

class ShaderLoader : public AssetLoader<Shader>
{
public:
	virtual Shader* Load(const std::string& filePath) override = 0;
};
