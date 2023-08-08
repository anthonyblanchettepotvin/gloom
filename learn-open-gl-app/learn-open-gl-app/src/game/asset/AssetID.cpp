#include "AssetID.h"

AssetID::AssetID(unsigned int value)
    : m_Value(value)
{
}

AssetID AssetID::Generate()
{
    static int nextValue = 0;

    return AssetID(nextValue++);
}
