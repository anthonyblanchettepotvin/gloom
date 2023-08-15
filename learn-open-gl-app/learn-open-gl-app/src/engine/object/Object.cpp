#include "Object.h"

#include "ObjectType.h"

Object::Object()
	: m_Id(ObjectID::Generate())
{
}

ObjectType Object::GetObjectType() const
{
	return ObjectType(typeid(*this));
}
