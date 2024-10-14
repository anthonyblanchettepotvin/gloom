#pragma once

#include <memory>

class GlFrame;
class GlTexture;

class GlTextureAttachment
{
public:
	void Initialize(size_t width, size_t height);

	void RenderToFrame(GlFrame& frame);

	unsigned int GetId() const;

private:
	std::unique_ptr<GlTexture> m_Texture = nullptr;
};
