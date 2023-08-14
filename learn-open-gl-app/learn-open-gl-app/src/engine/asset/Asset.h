#pragma once

#include <memory>

#include "../object/Object.h"

#include "AssetDescriptor.h"
#include "AssetID.h"

class Asset
{
public:
	Asset(const AssetDescriptor& assetDescriptor, std::unique_ptr<Object>& object);

	AssetID GetId() const { return m_Id; }

	AssetDescriptor GetDescriptor() const { return m_AssetDescriptor; }

	Object* GetObject() const { return m_Object.get(); }

	void SetName(const std::string& name) { m_Name = name; }
	std::string GetName() const { return m_Name; }

private:
	const AssetID m_Id;

	const AssetDescriptor m_AssetDescriptor;

	std::unique_ptr<Object> m_Object = nullptr;

	std::string m_Name = "";
};
