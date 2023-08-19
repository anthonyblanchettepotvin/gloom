#pragma once

#include <string>

#include "../../object/Object.h"

class Texture : public Object
{
public:
	Texture() = default;
	Texture(size_t width, size_t height, size_t channelCount, unsigned char* data, bool isFlippedVertically = false, bool isFlippedHorizontally = false);

	size_t GetWidth() const { return m_Width; }

	size_t GetHeight() const { return m_Height; }

	size_t GetChannelCount() const { return m_ChannelCount; }

	bool GetIsFlippedVertically() const { return m_IsFlippedVertically; }
	bool GetIsFlippedHorizontally() const { return m_IsFlippedHorizontally; }

	unsigned char* GetData() const { return m_Data; }

protected:
	size_t m_Width = 0;
	size_t m_Height = 0;
	size_t m_ChannelCount = 0;

	bool m_IsFlippedVertically = false;
	bool m_IsFlippedHorizontally = false;

	unsigned char* m_Data = nullptr;
};
