#pragma once

#include <memory>

enum class TextureFormat;

class GlFrame;
class GlTexture;

class GlTextureAttachment
{
public:
	virtual ~GlTextureAttachment() = default;

	void Initialize(size_t width, size_t height, TextureFormat format);

	void RenderToFrame(GlFrame& frame);

	unsigned int GetId() const;

private:
	std::unique_ptr<GlTexture> m_Texture = nullptr;
};
