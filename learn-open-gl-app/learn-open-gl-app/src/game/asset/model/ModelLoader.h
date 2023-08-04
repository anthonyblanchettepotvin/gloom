#pragma once

#include "../AssetLoader.h"

#include "Model.h"

class ModelLoader : public AssetLoader<Model>
{
public:
	virtual Model* Load(const std::string& filePath) override = 0;
};
