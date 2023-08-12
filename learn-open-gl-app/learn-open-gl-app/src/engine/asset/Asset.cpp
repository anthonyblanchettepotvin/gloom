#include "Asset.h"

Asset::Asset(const AssetDescriptor& assetDescriptor, std::unique_ptr<ObjectBase>& object)
	: m_AssetDescriptor(assetDescriptor), m_Object(std::move(object))
{
}
