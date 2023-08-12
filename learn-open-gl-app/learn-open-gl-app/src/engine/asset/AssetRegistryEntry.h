#pragma once

#include <memory>

#include "AssetDescriptor.h"

class AssetFactory;

class AssetRegistryEntry
{
public:
	AssetRegistryEntry(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory);

	AssetDescriptor GetDescriptor() const { return m_AssetDescriptor; }

	const AssetFactory& GetFactory() const { return *m_AssetFactory; }

private:
	AssetDescriptor m_AssetDescriptor;

	std::unique_ptr<AssetFactory> m_AssetFactory;
};
