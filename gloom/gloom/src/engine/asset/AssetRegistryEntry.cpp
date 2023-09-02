#include "AssetRegistryEntry.h"

#include <cassert>
#include <stdexcept>

#include "../EngineHelpers.h"

#include "AssetFactory.h"

AssetRegistryEntry::AssetRegistryEntry(const AssetDescriptor& assetDescriptor, std::unique_ptr<AssetFactory>& assetFactory)
	: m_AssetDescriptor(assetDescriptor)
{
	if (!assetFactory)
	{
		throw std::invalid_argument(ARGUMENT_IS_NULLPTR(assetFactory));
	}

	m_AssetFactory = std::move(assetFactory);
}
