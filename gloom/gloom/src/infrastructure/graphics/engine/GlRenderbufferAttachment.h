#pragma once

class GlRenderbufferAttachment
{
public:
	GlRenderbufferAttachment(size_t width, size_t height);

	unsigned int GetId() const { return m_Id; }

private:
	unsigned int m_Id;
};
