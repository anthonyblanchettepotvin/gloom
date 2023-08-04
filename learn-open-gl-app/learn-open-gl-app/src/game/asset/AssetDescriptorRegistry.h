#pragma once

#include <string>
#include <vector>

#include "AssetDescriptor.h"
#include "AssetDescriptorBase.h"

class AssetDescriptorRegistry
{
public:
	void Register(AssetDescriptorBase* assetDescriptor);
	void Unregister(AssetDescriptorBase* assetDescriptor);

	template<class T>
	AssetDescriptor<T>* Find();

private:
	std::vector<AssetDescriptorBase*> m_AssetDescriptors;
};

template<class T>
inline AssetDescriptor<T>* AssetDescriptorRegistry::Find()
{
	for (const auto& assetDescriptor : m_AssetDescriptors)
	{
		if (assetDescriptor->GetAssetType() == typeid(T))
		{
			return dynamic_cast<AssetDescriptor<T>*>(assetDescriptor);
		}
	}

	return nullptr;
}
