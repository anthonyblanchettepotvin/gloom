#pragma once

#include <string>

#include "../../object/Object.h"

class Texture : public Object
{
public:
	Texture() = default;
	Texture(size_t width, size_t height, size_t channelCount, unsigned char* data);

	size_t GetWidth() const { return m_Width; }

	size_t GetHeight() const { return m_Height; }

	size_t GetChannelCount() const { return m_ChannelCount; }

	unsigned char* GetData() const { return m_Data; }

protected:
	size_t m_Width;
	size_t m_Height;
	size_t m_ChannelCount;

	unsigned char* m_Data;
};
