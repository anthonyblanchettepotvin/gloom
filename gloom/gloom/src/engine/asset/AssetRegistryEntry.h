#pragma once

#include <cassert>
#include <memory>

#include "AssetDescriptor.h"

class AssetFactory;

class AssetRegistryEntry
{
public:
	AssetRegistryEntry(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory);

	AssetDescriptor GetDescriptor() const { return m_AssetDescriptor; }

	AssetFactory& GetFactory() { assert(m_AssetFactory != nullptr); return *m_AssetFactory; } // TODO: Not sure about this line.

private:
	AssetDescriptor m_AssetDescriptor;

	std::unique_ptr<AssetFactory> m_AssetFactory;
};
