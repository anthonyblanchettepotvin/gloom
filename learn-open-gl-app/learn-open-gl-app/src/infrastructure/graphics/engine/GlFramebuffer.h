#pragma once

#include "../texture/GlTexture.h"

#include "GlRenderbuffer.h"

class GlFramebuffer
{
public:
	GlFramebuffer(size_t width, size_t height);

	void Bind();
	void Unbind();

	bool CheckStatus();

	void BindRenderbuffer(const GlRenderbuffer& renderbuffer);
	void BindTexture(const GlTexture& texture);

private:
	unsigned int m_Id;
};
