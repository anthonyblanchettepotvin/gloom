#pragma once

#include <functional>

class ObjectID
{
private:
	ObjectID(unsigned int value);

public:
	static ObjectID Generate();

	inline bool operator==(const ObjectID& other) const noexcept
	{
		return this == &other || m_Value == other.m_Value;
	}

private:
	unsigned int m_Value;

	friend std::hash<ObjectID>;
};

template<>
struct std::hash<ObjectID>
{
	size_t operator()(ObjectID const& objId) const noexcept
	{
		return std::hash<unsigned int>{}(objId.m_Value);
	}
};
