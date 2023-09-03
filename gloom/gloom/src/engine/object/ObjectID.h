#pragma once

#include <functional>
#include <string>

class ObjectID
{
private:
	ObjectID(unsigned int value);

public:
	std::string ToString() const;

	static ObjectID Generate();

private:
	const unsigned int m_Value;

public:
	inline bool operator==(const ObjectID& other) const noexcept
	{
		return this == &other || m_Value == other.m_Value;
	}

	friend std::hash<ObjectID>;
};

template<>
struct std::hash<ObjectID>
{
	size_t operator()(ObjectID const& objectId) const noexcept
	{
		return std::hash<unsigned int>{}(objectId.m_Value);
	}
};
