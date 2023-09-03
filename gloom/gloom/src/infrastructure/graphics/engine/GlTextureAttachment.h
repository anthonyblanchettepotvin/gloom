#pragma once

#include "../texture/GlTexture.h"

class GlFrame;

class GlTextureAttachment
{
public:
	GlTextureAttachment(size_t width, size_t height);

	void RenderToFrame(GlFrame& frame);

	unsigned int GetId() const { return m_Texture.GetId(); }

private:
	GlTexture m_Texture;
};
