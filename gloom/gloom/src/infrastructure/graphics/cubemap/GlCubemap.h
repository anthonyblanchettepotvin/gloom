#pragma once

typedef unsigned int GLenum;

class Cubemap;

class GlCubemap
{
public:
	GlCubemap(const Cubemap& cubemap);

	void Use(unsigned int index);
	void Free();

	unsigned int GetId() const { return m_Id; }

private:
	GLenum ChannelCountToFormat(size_t channelCount) const;

	const Cubemap& m_Cubemap;

	unsigned int m_Id;
	unsigned int m_Index = 0;
};
