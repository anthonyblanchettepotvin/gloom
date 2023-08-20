#include "Texture.h"

Texture::Texture(size_t width, size_t height, size_t channelCount, unsigned char* data, bool isFlippedVertically, bool isFlippedHorizontally)
	: m_Width(width), m_Height(height), m_ChannelCount(channelCount), m_Data(data), m_IsFlippedVertically(isFlippedVertically), m_IsFlippedHorizontally(isFlippedHorizontally)
{
}
