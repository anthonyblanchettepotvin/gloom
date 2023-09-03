#include "GlTextureAttachment.h"

#include "../../../engine/graphics/texture/Texture.h"

#include "GlFrame.h"

GlTextureAttachment::GlTextureAttachment(size_t width, size_t height)
	: m_Texture(Texture(width, height, 3, nullptr))
{
}

void GlTextureAttachment::RenderToFrame(GlFrame& frame)
{
	frame.RenderTexture(m_Texture);
}
