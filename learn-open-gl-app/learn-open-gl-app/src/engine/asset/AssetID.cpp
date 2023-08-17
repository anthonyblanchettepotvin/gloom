#include "AssetID.h"

AssetID::AssetID(unsigned int value)
    : m_Value(value)
{
}

AssetID AssetID::Generate()
{
    static unsigned int nextValue = 0;

    return AssetID(nextValue++);
}

std::string AssetID::ToString() const
{
    return std::to_string(m_Value);
}
