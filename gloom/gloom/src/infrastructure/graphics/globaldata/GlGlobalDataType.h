#pragma once

class GlGlobalDataType
{
public:
	virtual void SendToDevice(unsigned int& offset) = 0;

	virtual unsigned int GetBaseAlignment() const = 0;
	virtual unsigned int GetSize() const = 0;
};
