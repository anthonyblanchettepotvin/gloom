#include "Asset.h"

Asset::Asset(const AssetDescriptor& assetDescriptor, const std::string& name, std::unique_ptr<Object>& object)
	: m_Id(AssetID::Generate()), m_AssetDescriptor(assetDescriptor), m_Name(name), m_Object(std::move(object))
{
}
