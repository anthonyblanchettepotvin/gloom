#pragma once

#include <typeindex>

class AssetDescriptorBase
{
public:
	AssetDescriptorBase(const std::type_index& assetType);
	AssetDescriptorBase(const AssetDescriptorBase& other);
	virtual ~AssetDescriptorBase() = default;

	std::type_index GetAssetType() const { return m_AssetType; }

	AssetDescriptorBase& operator=(const AssetDescriptorBase& other)
	{
		if (this == &other)
			return *this;

		m_AssetType = other.m_AssetType;

		return *this;
	}

	inline bool operator==(const AssetDescriptorBase& other) const noexcept
	{
		return this == &other || m_AssetType == other.m_AssetType;
	}

private:
	std::type_index m_AssetType;
};
