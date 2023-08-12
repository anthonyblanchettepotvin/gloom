#pragma once

#include <typeindex>

class ObjectType final
{
public:
	ObjectType(const std::type_index& typeIndex);

	inline bool operator==(const ObjectType& other) const noexcept
	{
		return this == &other || m_TypeIndex == other.m_TypeIndex;
	}

private:
	std::type_index m_TypeIndex;

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
