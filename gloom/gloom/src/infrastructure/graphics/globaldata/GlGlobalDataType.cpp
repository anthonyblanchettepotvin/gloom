#include "GlGlobalDataType.h"

#include "../../../engine/math/Math.hpp"

void GlGlobalDataType::AddAlignedSizeToTotalSize(unsigned int& totalSize) const
{
	totalSize = Math::Align(totalSize, GetBaseAlignment()) + GetSize();
}
