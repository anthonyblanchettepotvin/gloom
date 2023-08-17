#pragma once

#include <memory>
#include <string>

#include "../object/Object.h"

#include "AssetDescriptor.h"
#include "AssetID.h"

class Asset
{
public:
	Asset(const AssetDescriptor& assetDescriptor, const std::string& name, std::unique_ptr<Object>& object);

	AssetID GetId() const { return m_Id; }

	AssetDescriptor GetDescriptor() const { return m_AssetDescriptor; }

	void SetName(const std::string& name) { m_Name = name; }
	std::string GetName() const { return m_Name; }

	Object* GetObject() const { return m_Object.get(); }

private:
	const AssetID m_Id;

	const AssetDescriptor m_AssetDescriptor;
	
	std::string m_Name;

	std::unique_ptr<Object> m_Object = nullptr;
};
