#pragma once

#include "AssetDescriptorRegistry.h"

class AssetController
{
public:
	AssetController(const AssetDescriptorRegistry& assetDescriptorRegistry);

	template<class T>
	T* LoadAsset(const std::string& filePath);

private:
	AssetDescriptorRegistry m_AssetDescriptorRegistry;
};

template<class T>
inline T* AssetController::LoadAsset(const std::string& filePath)
{
	AssetDescriptor<T>* assetDescriptor = m_AssetDescriptorRegistry.Find<T>();
	if (assetDescriptor)
	{
		return assetDescriptor->GetAssetLoader().Load(filePath);
	}

	return nullptr;
}
