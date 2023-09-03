#pragma once

class GlRenderbufferAttachment;
class GlTextureAttachment;

class GlFramebuffer
{
public:
	GlFramebuffer(size_t width, size_t height);

	void Bind();
	void Unbind();

	void AttachRenderbuffer(const GlRenderbufferAttachment& renderbufferAttachment);
	void AttachTexture(const GlTextureAttachment& textureAttachment);

	bool IsComplete();

private:
	unsigned int m_Id;
};
