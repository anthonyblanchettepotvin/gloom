#pragma once

#include "../../../engine/math/Math.hpp"

template<typename T>
class GlUniformBufferDataType
{
public:
	void AddAlignedSizeToTotalSize(unsigned int& totalSize) const;

	virtual void SendToDevice(const T& value, unsigned int& offset) = 0;

	virtual unsigned int GetBaseAlignment() const = 0;
	virtual unsigned int GetSize() const = 0;
};

template<typename T>
void GlUniformBufferDataType<T>::AddAlignedSizeToTotalSize(unsigned int& totalSize) const
{
	totalSize = Math::Align(totalSize, GetBaseAlignment()) + GetSize();
}
