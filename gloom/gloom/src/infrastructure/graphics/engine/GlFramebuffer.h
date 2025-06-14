#pragma once

#include <memory>
#include <vector>

class GlRenderbufferAttachment;
class GlTextureAttachment;

typedef unsigned int GLenum;

class GlFramebuffer
{
public:
	void Initialize();

	void Bind();
	void Unbind();

	void AttachRenderbuffer(const GlRenderbufferAttachment& renderbufferAttachment);
	void AttachTexture(std::unique_ptr<GlTextureAttachment>& textureAttachment);

	bool IsComplete();

private:
	unsigned int m_Id;

	std::vector<std::unique_ptr<GlTextureAttachment>> m_TextureAttachments;
	std::vector<GLenum> m_TextureAttachmentsAttachment;
};
