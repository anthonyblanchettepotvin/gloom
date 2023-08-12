#pragma once

#include <string>
#include <typeindex>

class AssetType final
{
public:
	AssetType(const std::type_index& typeIndex);

	inline bool operator==(const AssetType& other) const noexcept
	{
		return this == &other || m_TypeIndex == other.m_TypeIndex;
	}

private:
	std::type_index m_TypeIndex;

	friend std::hash<AssetType>;
};

template<>
struct std::hash<AssetType>
{
	size_t operator()(const AssetType& assetType) const
	{
		return std::hash<std::type_index>{}(assetType.m_TypeIndex);
	}
};

class AssetDescriptor final
{
public:
	AssetDescriptor(const AssetType& assetType, const std::string& displayName);

	AssetType GetAssetType() const { return m_AssetType; }

private:
	AssetType m_AssetType;

	std::string m_DisplayName;
};
