#pragma once

#include <memory>

#include "../object/Object.h"

#include "AssetDescriptor.h"

class Asset
{
public:
	Asset(const AssetDescriptor& assetDescriptor, std::unique_ptr<Object>& object);

	AssetDescriptor GetAssetDescriptor() const { return m_AssetDescriptor; }

	Object* GetObject() const { return m_Object.get(); }

private:
	AssetDescriptor m_AssetDescriptor;

	std::unique_ptr<Object> m_Object = nullptr;
};
