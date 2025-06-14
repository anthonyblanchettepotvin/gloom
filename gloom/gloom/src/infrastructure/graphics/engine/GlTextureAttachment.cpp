#include "GlTextureAttachment.h"

#include "../../../engine/graphics/texture/Texture.h"

#include "../texture/GlTexture.h"

#include "GlFrame.h"

void GlTextureAttachment::Initialize(size_t width, size_t height, TextureFormat format)
{
	m_Texture = std::make_unique<GlTexture>(Texture(width, height, format, nullptr));
}

void GlTextureAttachment::RenderToFrame(GlFrame& frame)
{
	frame.RenderTexture(*m_Texture);
}

unsigned int GlTextureAttachment::GetId() const
{
	return m_Texture->GetId();
}
