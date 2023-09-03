#pragma once

typedef unsigned int GLenum;

class Texture;

class GlTexture
{
public:
	GlTexture(const Texture& texture);

	void Use(unsigned int index);
	void Free();

	unsigned int GetId() const { return m_Id; }

private:
	GLenum ChannelCountToFormat(size_t channelCount) const;

	const Texture& m_Texture;

	unsigned int m_Id;
	unsigned int m_Index = 0;
};
