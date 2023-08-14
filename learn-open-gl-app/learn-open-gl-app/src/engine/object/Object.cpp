#include "Object.h"

#include "ObjectType.h"

ObjectBase::ObjectBase()
	: m_Id(ObjectID::Generate())
{
}

ObjectType ObjectBase::GetObjectType() const
{
	return ObjectType(typeid(*this));
}
