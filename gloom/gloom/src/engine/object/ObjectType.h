#pragma once

#include <string>
#include <typeindex>

class ObjectType
{
public:
	ObjectType(const std::type_index& typeIndex);

	std::string GetDisplayName() const { return m_TypeIndex.name(); }

private:
	const std::type_index m_TypeIndex;

public:
	inline bool operator==(const ObjectType& other) const noexcept
	{
		return this == &other || m_TypeIndex == other.m_TypeIndex;
	}

	inline bool operator!=(const ObjectType& other) const noexcept
	{
		return !(*this == other);
	}

	friend std::hash<ObjectType>;
};

template<>
struct std::hash<ObjectType>
{
	size_t operator()(const ObjectType& objectType) const
	{
		return std::hash<std::type_index>{}(objectType.m_TypeIndex);
	}
};
