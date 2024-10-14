#pragma once

class GlRenderbufferAttachment;
class GlTextureAttachment;

class GlFramebuffer
{
public:
	void Initialize();

	void Bind();
	void Unbind();

	void AttachRenderbuffer(const GlRenderbufferAttachment& renderbufferAttachment);
	void AttachTexture(const GlTextureAttachment& textureAttachment);

	bool IsComplete();

private:
	unsigned int m_Id;
};
