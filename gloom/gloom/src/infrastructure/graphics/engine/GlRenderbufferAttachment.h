#pragma once

class GlRenderbufferAttachment
{
public:
	void Initialize(size_t width, size_t height);

	unsigned int GetId() const { return m_Id; }

private:
	unsigned int m_Id;
};
