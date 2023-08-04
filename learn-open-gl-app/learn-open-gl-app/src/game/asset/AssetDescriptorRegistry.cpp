#include "AssetDescriptorRegistry.h"

void AssetDescriptorRegistry::Register(AssetDescriptorBase* assetDescriptor)
{
	auto it = std::find(m_AssetDescriptors.begin(), m_AssetDescriptors.end(), assetDescriptor);
	if (it == m_AssetDescriptors.end())
	{
		m_AssetDescriptors.push_back(assetDescriptor);
	}
}

void AssetDescriptorRegistry::Unregister(AssetDescriptorBase* assetDescriptor)
{
	auto it = std::find(m_AssetDescriptors.begin(), m_AssetDescriptors.end(), assetDescriptor);
	if (it != m_AssetDescriptors.end())
	{
		m_AssetDescriptors.erase(it);
	}
}
