#pragma once

#include <functional>
#include <string>
#include <typeindex>

#include "ObjectID.h"
#include "ObjectType.h"

class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase() = default;

	ObjectID GetId() const { return m_Id; }

	ObjectType GetObjectType() const { return ObjectType(typeid(*this)); }

private:
	const ObjectID m_Id;

public:
	inline bool operator==(const ObjectBase& other) const noexcept
	{
		return this == &other || m_Id == other.m_Id;
	}

	friend std::hash<ObjectBase>;
};

template<>
struct std::hash<ObjectBase>
{
	size_t operator()(ObjectBase const& obj) const noexcept
	{
		return std::hash<ObjectID>{}(obj.m_Id);
	}
};

template<class T>
class Object : public ObjectBase
{
public:
	static ObjectType GetObjectType() { return ObjectType(typeid(T)); }
};
