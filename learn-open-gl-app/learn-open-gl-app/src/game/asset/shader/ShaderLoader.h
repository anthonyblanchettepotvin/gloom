#pragma once

#include "../../../engine/graphics/shader/Shader.h"

#include "../AssetLoader.h"

class ShaderLoader : public AssetLoader<Shader>
{
public:
	virtual Shader* Load(const std::string& filePath) override = 0;
};
