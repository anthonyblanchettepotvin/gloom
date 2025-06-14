#pragma once

typedef unsigned int GLenum;

enum class TextureFormat;

class Texture;

class GlTexture
{
public:
	GlTexture(const Texture& texture);

	void Use(unsigned int index);
	void Free();

	unsigned int GetId() const { return m_Id; }

private:
	GLenum TextureFormatToGlInternalFormat(const TextureFormat& textureFormat) const;
	GLenum TextureFormatToGlFormat(const TextureFormat& textureFormat) const;
	GLenum TextureFormatToGlType(const TextureFormat& textureFormat) const;

	const Texture& m_Texture;

	unsigned int m_Id;
	unsigned int m_Index = 0;
};
