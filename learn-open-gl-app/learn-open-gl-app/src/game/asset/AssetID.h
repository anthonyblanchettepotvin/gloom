#pragma once

#include <functional>

class AssetID
{
private:
	AssetID(unsigned int value);

public:
	static AssetID Generate();

	/*inline bool operator==(const AssetID& other) const noexcept
	{
		return this == &other || m_Value == other.m_Value;
	}

	friend std::hash<AssetID>;*/

private:
	unsigned int m_Value;
};

//template<>
//struct std::hash<AssetID>
//{
//	size_t operator()(AssetID const& assetId) const noexcept
//	{
//		return std::hash<unsigned int>{}(assetId.m_Value);
//	}
//};
