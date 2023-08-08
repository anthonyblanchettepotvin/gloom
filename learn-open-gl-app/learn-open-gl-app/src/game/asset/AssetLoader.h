#pragma once

#include <string>

template<class T>
class AssetLoader
{
public:
	virtual T* Load(const std::string& filePath) = 0;
};
