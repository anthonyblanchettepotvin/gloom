#pragma once

#include <functional>
#include <string>

class AssetID
{
private:
	AssetID(unsigned int value);

public:
	std::string ToString() const;

	static AssetID Generate();

private:
	const unsigned int m_Value;

public:
	inline bool operator==(const AssetID& other) const noexcept
	{
		return this == &other || m_Value == other.m_Value;
	}

	friend std::hash<AssetID>;
};

template<>
struct std::hash<AssetID>
{
	size_t operator()(AssetID const& assetId) const noexcept
	{
		return std::hash<unsigned int>{}(assetId.m_Value);
	}
};
