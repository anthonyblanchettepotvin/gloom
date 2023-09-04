#pragma once

class GlGlobalDataType
{
public:
	void AddAlignedSizeToTotalSize(unsigned int& totalSize) const;

	virtual void SendToDevice(unsigned int& offset) = 0;

	virtual unsigned int GetBaseAlignment() const = 0;
	virtual unsigned int GetSize() const = 0;
};
