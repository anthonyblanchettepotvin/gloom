#pragma once

#include <functional>
#include <string>

#include "AssetID.h"

class Asset
{
public:
	Asset();

	/*inline bool operator==(const Asset& other) const noexcept
	{
		return this == &other || m_Id == other.m_Id;
	}

	friend std::hash<Asset>;*/

	const AssetID GetId() const { return m_Id; }

	void SetName(const std::string& name) { m_Name = name; }
	std::string GetName() const { return m_Name; }

private:
	const AssetID m_Id;

	std::string m_Name;
};

//template<>
//struct std::hash<Asset>
//{
//	size_t operator()(Asset const& asset) const noexcept
//	{
//		return std::hash<AssetID>{}(asset.m_Id);
//	}
//};
