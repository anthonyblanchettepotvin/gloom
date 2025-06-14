#pragma once

#include <algorithm>
#include <unordered_map>

#include "../../object/Object.h"

enum class TextureFormat
{
	R,
	RG,
	RGB,
	RGBA,
	RGBA16F
};

enum class TextureFormatComponent
{
	R,
	G,
	B,
	A
};

struct TextureFormatComponentInfo
{
public:
	TextureFormatComponentInfo(TextureFormatComponent component, size_t bitDepth);

	size_t GetBitDepth() const { return m_BitDepth; }

private:
	TextureFormatComponent m_Component;

	size_t m_BitDepth;
};

struct TextureFormatInfo
{
public:
	TextureFormatInfo() = default;
	TextureFormatInfo(const std::vector<TextureFormatComponentInfo>& componentsInfo);

	const std::vector<TextureFormatComponentInfo>& GetComponentsInfo() const { return m_ComponentsInfo; }

private:
	std::vector<TextureFormatComponentInfo> m_ComponentsInfo;
};

static std::unordered_map<TextureFormat, TextureFormatInfo> TextureFormatInfoRegistry = {
	{
		TextureFormat::R,
		TextureFormatInfo(
			{
				TextureFormatComponentInfo(TextureFormatComponent::R, 8)
			}
		)
	},
	{
		TextureFormat::RG,
		TextureFormatInfo(
			{
				TextureFormatComponentInfo(TextureFormatComponent::R, 8),
				TextureFormatComponentInfo(TextureFormatComponent::G, 8)
			}
		)
	},
	{
		TextureFormat::RGB,
		TextureFormatInfo(
			{
				TextureFormatComponentInfo(TextureFormatComponent::R, 8),
				TextureFormatComponentInfo(TextureFormatComponent::G, 8),
				TextureFormatComponentInfo(TextureFormatComponent::B, 8)
			}
		)
	},
	{
		TextureFormat::RGBA,
		TextureFormatInfo(
			{
				TextureFormatComponentInfo(TextureFormatComponent::R, 8),
				TextureFormatComponentInfo(TextureFormatComponent::G, 8),
				TextureFormatComponentInfo(TextureFormatComponent::B, 8),
				TextureFormatComponentInfo(TextureFormatComponent::A, 8)
			}
		)
	},
	{
		TextureFormat::RGBA16F,
		TextureFormatInfo(
			{
				TextureFormatComponentInfo(TextureFormatComponent::R, 16),
				TextureFormatComponentInfo(TextureFormatComponent::G, 16),
				TextureFormatComponentInfo(TextureFormatComponent::B, 16),
				TextureFormatComponentInfo(TextureFormatComponent::A, 16)
			}
		)
	}
};

static const TextureFormat* FindTextureFormat(size_t componentCount, size_t bitDepth)
{
	for (const auto& entry : TextureFormatInfoRegistry)
	{
		const TextureFormatInfo& textureFormatInfo = entry.second;

		if (textureFormatInfo.GetComponentsInfo().size() == componentCount
			&& std::all_of(
				textureFormatInfo.GetComponentsInfo().begin(),
				textureFormatInfo.GetComponentsInfo().end(),
				[bitDepth](const TextureFormatComponentInfo& textureFormatComponentInfo) { return textureFormatComponentInfo.GetBitDepth() == bitDepth; }))
			return &entry.first;
	}

	return nullptr;
}

class Texture : public Object
{
public:
	Texture() = default;
	Texture(size_t width, size_t height, TextureFormat format, void* data, bool isFlippedVertically = false, bool isFlippedHorizontally = false);

	size_t GetWidth() const { return m_Width; }
	size_t GetHeight() const { return m_Height; }

	size_t GetComponentCount() const { return TextureFormatInfoRegistry[m_Format].GetComponentsInfo().size(); }

	TextureFormat GetFormat() const { return m_Format; }

	bool GetIsFlippedVertically() const { return m_IsFlippedVertically; }
	bool GetIsFlippedHorizontally() const { return m_IsFlippedHorizontally; }

	const void* GetData() const { return m_Data; }

private:
	size_t m_Width = 0;
	size_t m_Height = 0;

	TextureFormat m_Format = TextureFormat::RGBA16F;

	bool m_IsFlippedVertically = false;
	bool m_IsFlippedHorizontally = false;

	const void* m_Data = nullptr;
};
