#pragma once

#include <functional>
#include <string>

#include "ObjectID.h"

class Object
{
public:
	Object();
	virtual ~Object() = default;

	inline bool operator==(const Object& other) const noexcept
	{
		return this == &other || m_Id == other.m_Id;
	}

	const ObjectID GetId() const { return m_Id; }

	void SetName(const std::string& name) { m_Name = name; }
	std::string GetName() const { return m_Name; }

private:
	const ObjectID m_Id;

	std::string m_Name;

	friend std::hash<Object>;
};

template<>
struct std::hash<Object>
{
	size_t operator()(Object const& obj) const noexcept
	{
		return std::hash<ObjectID>{}(obj.m_Id);
	}
};
