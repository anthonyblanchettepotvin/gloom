#pragma once

#include <string>

#include "../object/ObjectType.h"

class AssetDescriptor final
{
public:
	AssetDescriptor(const ObjectType& objectType, const std::string& displayName);

	ObjectType GetObjectType() const { return m_ObjectType; }

	std::string GetDisplayName() const { return m_DisplayName; }

private:
	ObjectType m_ObjectType;

	std::string m_DisplayName;
};
