#pragma once

#include <memory>

#include "../object/Object.h"

#include "AssetDescriptor.h"

class Asset
{
public:
	Asset(const AssetDescriptor& assetDescriptor, std::unique_ptr<ObjectBase>& object);

	AssetDescriptor GetAssetDescriptor() const { return m_AssetDescriptor; }

	ObjectBase* GetObject() const { return m_Object.get(); }

	void SetName(const std::string& name) { m_Name = name; }
	std::string GetName() const { return m_Name; }

private:
	AssetDescriptor m_AssetDescriptor;

	std::unique_ptr<ObjectBase> m_Object = nullptr;

	std::string m_Name = "";
};
