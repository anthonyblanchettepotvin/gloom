#pragma once

#include <functional>
#include <string>
#include <typeindex>

#include "ObjectID.h"

class ObjectType;

class Object
{
public:
	Object();
	virtual ~Object() = default;

	ObjectID GetId() const { return m_Id; }

	ObjectType GetObjectType() const;

private:
	const ObjectID m_Id;

public:
	inline bool operator==(const Object& other) const noexcept
	{
		return this == &other || m_Id == other.m_Id;
	}

	friend std::hash<Object>;
};
