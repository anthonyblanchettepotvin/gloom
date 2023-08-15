#include "Asset.h"

Asset::Asset(const AssetDescriptor& assetDescriptor, std::unique_ptr<Object>& object)
	: m_Id(AssetID::Generate()), m_AssetDescriptor(assetDescriptor), m_Object(std::move(object))
{
}
