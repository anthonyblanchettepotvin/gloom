#pragma once

class GlGlobalDataType
{
public:
	virtual unsigned int GetBaseAlignment() = 0;
	virtual unsigned int GetSize() = 0;

	virtual void SendToDevice(unsigned int& offset) = 0;
};
