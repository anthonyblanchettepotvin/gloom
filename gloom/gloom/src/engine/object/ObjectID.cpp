#include "ObjectID.h"

ObjectID::ObjectID(unsigned int value)
    : m_Value(value)
{
}

ObjectID ObjectID::Generate()
{
    static unsigned int nextValue = 0;

    return ObjectID(nextValue++);
}

std::string ObjectID::ToString() const
{
    return std::to_string(m_Value);
}
