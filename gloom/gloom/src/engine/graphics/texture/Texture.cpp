#include "Texture.h"

TextureFormatComponentInfo::TextureFormatComponentInfo(TextureFormatComponent component, size_t bitDepth)
	: m_Component(component)
	, m_BitDepth(bitDepth)
{
}

TextureFormatInfo::TextureFormatInfo(const std::vector<TextureFormatComponentInfo>& componentsInfo)
	: m_ComponentsInfo(componentsInfo)
{
}


Texture::Texture(size_t width, size_t height, TextureFormat format, void* data, bool isFlippedVertically, bool isFlippedHorizontally)
	: m_Width(width)
	, m_Height(height)
	, m_Format(format)
	, m_Data(data)
	, m_IsFlippedVertically(isFlippedVertically)
	, m_IsFlippedHorizontally(isFlippedHorizontally)
{
}